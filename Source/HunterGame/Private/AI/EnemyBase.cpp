// Hunter Game by Gamer Guru.


#include "AI/EnemyBase.h"
#include "AI/AIControllerBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TimerManager.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
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

	AIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	AIController->RunBehaviorTree(BehaviorTree);
}

/** Interface **/
EAIState AEnemyBase::GetEnemyState() const
{
	return AIState;
}
/** Interface **/
