// Hunter Game by Gamer Guru.


#include "AI/EnemyBase.h"
#include "AI/AIControllerBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TimerManager.h"
#include "Weapon/Weapon.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	Init_Weapon();
}

void AEnemyBase::Init_Weapon()
{
	if (!GetWorld()) return;
	
	if (WeaponClass)
	{
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Owner = this;
		ActorSpawnParameters.Instigator = this;
		//AActor* Weapon_Actor = GetWorld()->SpawnActor(WeaponClass, GetActorTransform(), ActorSpawnParameters);
		AActor* Weapon_Actor = GetWorld()->SpawnActor(WeaponClass);

		Weapon = Cast<AWeapon>(Weapon_Actor);
		if (Weapon)
		{
			Weapon->SetOwner(this);
			FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget,
				EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
			Weapon->AttachToComponent(GetMesh(), AttachmentTransformRules, Weapon->GetOutHandAttachSocketName());
		}
	}
}

void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
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

/** Interface **/
EAIState AEnemyBase::GetEnemyState() const
{
	if (AIController == nullptr) return AIState;
	return AIController->GetEnemyAIState();
}
/** Interface **/
