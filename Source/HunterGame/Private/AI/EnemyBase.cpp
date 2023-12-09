// Hunter Game by Gamer Guru.


#include "AI/EnemyBase.h"
#include "AI/AIControllerBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TimerManager.h"
#include "Component/StatsComponent.h"
#include "Component/AIEnemy/AIEnemyCombatComponent.h"
#include "Weapon/Weapon.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;

	CombatComponent = CreateDefaultSubobject<UAIEnemyCombatComponent>(TEXT("Enemy Combat Component"));
	StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	if (CombatComponent)
	{
		CombatComponent->OwnerAIEnemy = this;
		CombatComponent->Init_Weapon();
	}
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

	if (StatsComponent)
	{
		StatsComponent->OwnerHuman = this;
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
	if (!CombatComponent) return;
	CombatComponent->Attack();
}
/** Combat **/

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
