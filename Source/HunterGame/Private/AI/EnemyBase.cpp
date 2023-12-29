// Hunter Game by Gamer Guru.


#include "AI/EnemyBase.h"
#include "AI/AIControllerBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TimerManager.h"
#include "Actor/Enemy_Group_Manager.h"
#include "AI/EnemyGroupLeader_Base.h"
#include "AI/EnemyGroupMember_Base.h"
#include "Component/StatsComponent.h"
#include "Component/AIEnemy/AIEnemyCombatComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Damage.h"
#include "Weapon/Weapon.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Tags.AddUnique(FName("Character"));
	Tags.AddUnique(FName("Human"));
	Tags.AddUnique(FName("EnemyBase"));
	Tags.AddUnique(FName("Enemy"));
	Tags.AddUnique(FName("AIEnemy"));

	GetCharacterMovement()->bOrientRotationToMovement = true;

	const FVector RelativeMeshLocation = FVector(0.f, 0.f, -90.f);
	GetMesh()->SetRelativeLocation(RelativeMeshLocation);
	const FRotator RelativeMeshRotation = FRotator(0.f, -90.f, 0.f);
	GetMesh()->SetRelativeRotation(RelativeMeshRotation);

	CombatComponent = CreateDefaultSubobject<UAIEnemyCombatComponent>(TEXT("Enemy Combat Component"));
	StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));

	if (EnemyGroupManager)
	{
		EnemyGroupManager->Initial_GroupSize = 1;
		EnemyGroupManager->CurrentGroupSize = 1;
	}
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	OnTakeAnyDamage.AddDynamic(this, &AEnemyBase::ReceiveDamage);
	if (bIsLeader)
	{
		Init_GroupManager();
	}
}

void AEnemyBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!HasAuthority()) return;
	
	AIController = Cast<AAIControllerBase>(NewController);

	if (AIController && AIController->GetBlackboardComponent() && BehaviorTree)
	{
		AIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		AIController->RunBehaviorTree(BehaviorTree);
	}
}

void AEnemyBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (CombatComponent)
	{
		CombatComponent->OwnerAIEnemy = this;
		CombatComponent->Init_Weapon();
	}
	
	if (StatsComponent)
	{
		StatsComponent->OwnerHuman = this;
		StatsComponent->Init_Attributes();
	}
}

float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if (AIController)
	{
		if (AIController->GetEnemyAIState() < EAIState::EAIS_Chasing)
		{
			AIController->SetBBTargetActor(DamageCauser);
			AIController->SetStateAsChasing(DamageCauser);
		}
	}
	// Report Damage Event
	ReportDamageEvent(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AEnemyBase::GetHit(FName HitBoneName, FVector HitBoneLocation)
{
	//IHitInterface::GetHit();
	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Cyan, HitBoneName.ToString());
}

USkinnedMeshComponent* AEnemyBase::GetCharacterMesh()
{
	return GetMesh();
}

void AEnemyBase::ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                               AController* InstigatorController, AActor* DamageCauser)
{
	if (StatsComponent)
	{
		StatsComponent->Health_Data.CurrentValue = FMath::Clamp(
		StatsComponent->Health_Data.CurrentValue - Damage, 0.f, StatsComponent->MaxHealth_Data.CurrentValue);
		if (StatsComponent->Health_Data.CurrentValue <= 0)
		{
			// TODO: Temporary
			if (CombatComponent->Weapon)
			{
				CombatComponent->Weapon->Destroy();
			}

			// Death
			OnDeath();
		}
	}
}

void AEnemyBase::ReportDamageEvent(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	UAIPerceptionSystem* PerceptionSystem = UAIPerceptionSystem::GetCurrent(this);
	if (PerceptionSystem)
	{
		FAIDamageEvent Event(this, DamageCauser, DamageAmount, GetActorLocation(), GetActorLocation());
		PerceptionSystem->OnEvent(Event);
	}
}

void AEnemyBase::OnDeath()
{
	Destroy();
}

/** Interface **/
EAIState AEnemyBase::GetEnemyState() const
{
	if (AIController == nullptr) return EAIState::EAIS_None;
	return AIController->GetEnemyAIState();
}
/** Interface **/

/** Combat **/
bool AEnemyBase::ToggleWeapon()
{
	if (CombatComponent == nullptr) return false;
	CombatComponent->ToggleWeapon();
	return true;
}

void AEnemyBase::ToggleWeaponAnimNotifyCallBack()
{
	GEngine->AddOnScreenDebugMessage(-1, 123.f, FColor::Orange, FString("Toggle combat called for AI enemy(Poachers/Hunters)"));
	if (CombatComponent == nullptr) return;
	CombatComponent->ToggleWeaponAnimNotifyCallBack();
}

void AEnemyBase::UpdateAttackRadius()
{
	AIController->UpdateAttackRadius(GetOwnedWeapon());
}

void AEnemyBase::Attack()
{
	if (!CombatComponent || AIActionState != EAIEnemyActionState::EAIAS_None) return;
	CombatComponent->Attack();
}
/** Combat **/

void AEnemyBase::OnAttackCompletedAnimNotifyCallBack()
{
	AIActionState = EAIEnemyActionState::EAIAS_None;
}

void AEnemyBase::OnAIStateSetAsRunningAway()
{
	if (CombatComponent == nullptr) return;
	CombatComponent->OnAIStateSetAsRunningAway();
}

void AEnemyBase::OnPoacherGroupMemberStateChanged(AEnemyBase* Member)
{
	if (AEnemyGroupMember_Base* PoacherGroupMember = Cast<AEnemyGroupMember_Base>(Member))
	{
		if (PoacherGroupMember->GetLeader() == nullptr || PoacherGroupMember->GetLeader()->AIController == nullptr) return;
		
		switch (Member->GetAIState())
		{
			case EAIState::EAIS_None:
				break;
			case EAIState::EAIS_Passive:
				PoacherGroupMember->GetLeader()->AIController->SetStateAsPassive();
				break;
			case EAIState::EAIS_Hunting:
				PoacherGroupMember->GetLeader()->AIController->SetStateAsHunting(Member->Get_TargetActor_BB());
				break;
			case EAIState::EAIS_Investigating:
				PoacherGroupMember->GetLeader()->AIController->SetStateAsInvestigating();
				break;
			case EAIState::EAIS_Chasing:
				PoacherGroupMember->GetLeader()->AIController->SetStateAsChasing(Member->Get_TargetActor_BB());
				break;
			case EAIState::EAIS_Attacking:
				PoacherGroupMember->GetLeader()->AIController->SetStateAsAttacking(Member->Get_TargetActor_BB());
				break;
			case EAIState::EAIS_Retreating:
				PoacherGroupMember->GetLeader()->AIController->SetStateAsRetreating();
				break;
			case EAIState::EAIS_RunningAway:
				PoacherGroupMember->GetLeader()->AIController->SetStateAsRunningAway();
				break;
			default:
				break;
		}
	}
}

void AEnemyBase::Init_GroupManager()
{
	if (EnemyGroupManager) return;
	
	TArray<AActor*> GroupManagerActors;
	UGameplayStatics::GetAllActorsOfClass(this, AEnemy_Group_Manager::StaticClass(), GroupManagerActors);
	for (const auto GroupManager : GroupManagerActors)
	{
		if (GroupManager)
		{
			if (AEnemy_Group_Manager* Enemy_Group_Manager = Cast<AEnemy_Group_Manager>(GroupManager))
			{
				if (Enemy_Group_Manager->GroupId == GroupId)
				{
					EnemyGroupManager = Enemy_Group_Manager;
					EnemyGroupManager->NPC_Enemies.Add(this);
				}
			}
		}
	}
}

/** Getter / Setter **/
AWeapon* AEnemyBase::GetOwnedWeapon() const
{
	return CombatComponent->Weapon;
}

bool AEnemyBase::HaveWeaponInHand() const
{
	if (GetOwnedWeapon() && GetOwnedWeapon()->GetWeaponAttachmentStatus() == EAttachmentStatus::EAS_InHand)
	{
		return true;
	}
	else
	{
		return false;
	}
}

FVector AEnemyBase::GetHitTarget() const
{
	if (!AIController) return FVector();
	if (AActor* TargetActorBB = Get_TargetActor_BB())
	{
		// TODO: Calculate random deviation vector based on the distance between the AI enemy and the hit target
		//float DistanceBetween = GetActorLocation().Size() - TargetActorBB->GetActorLocation().Size();

		FVector RandomDeviationVector = FVector(FMath::FRandRange(-4.f, 4.f),
			FMath::FRandRange(-4.f, 4.f), FMath::FRandRange(-4.f, 4.f));
		
		// Aim at head (expensive operation(Cast))  // TODO: Find a way to optimize this
		if (ACharacter* Character = Cast<ACharacter>(TargetActorBB))
		{
			FTransform TargetCharacterHeadTransform = Character->GetMesh()->GetSocketTransform(FName("head"), RTS_World);
			FVector TargetCharacterHeadLocation = TargetCharacterHeadTransform.GetLocation();
			return  TargetCharacterHeadLocation + RandomDeviationVector;
			//return TargetCharacterHeadLocation;
		}
		else
		{
			return TargetActorBB->GetActorLocation() + RandomDeviationVector;
		}
	}
	return FVector();
}

AActor* AEnemyBase::Get_TargetActor_BB() const
{
	if (AIController)
	{
		return AIController->GetTargetActorBB();
	}
	
	return nullptr;
}

EAIState AEnemyBase::GetAIState() const
{
	if (AIController == nullptr) {return EAIState::EAIS_None;}
	return AIController->GetEnemyAIState();	
}

void AEnemyBase::SetEnemyActionState(EAIEnemyActionState InActionState)
{
	AIActionState = InActionState;
}

void AEnemyBase::SetGroupId(int32 InId)
{
	GroupId = InId;
}
/** Getter / Setter **/
