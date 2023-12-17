// Hunter Game by Gamer Guru.


#include "AI/EnemyBase.h"
#include "AI/AIControllerBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TimerManager.h"
#include "Component/StatsComponent.h"
#include "Component/AIEnemy/AIEnemyCombatComponent.h"
#include "Engine/DamageEvents.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Damage.h"
#include "Weapon/Weapon.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;
	Tags.AddUnique(FName("EnemyBase"));
	Tags.AddUnique(FName("Enemy"));
	Tags.AddUnique(FName("AIEnemy"));

	CombatComponent = CreateDefaultSubobject<UAIEnemyCombatComponent>(TEXT("Enemy Combat Component"));
	StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	OnTakeAnyDamage.AddDynamic(this, &AEnemyBase::ReceiveDamage);
}

void AEnemyBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!HasAuthority()) return;
	
	AIController = Cast<AAIControllerBase>(NewController);

	if (BehaviorTree)
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

void AEnemyBase::GetHit()
{
	IHitInterface::GetHit();
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
			Destroy();
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

/** Interface **/
EAIState AEnemyBase::GetEnemyState() const
{
	if (AIController == nullptr) return AIState;
	return AIController->GetEnemyAIState();
}
/** Interface **/

/** Combat **/
void AEnemyBase::ToggleWeapon()
{
	if (CombatComponent == nullptr) return;
	CombatComponent->ToggleWeapon();
}

void AEnemyBase::ToggleWeaponAnimNotifyCallBack()
{
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

void AEnemyBase::SetEnemyActionState(EAIEnemyActionState InActionState)
{
	AIActionState = InActionState;
}
/** Getter / Setter **/
