// Hunter Game by Gamer Guru.


#include "AI/EnemyBase.h"
#include "AsyncTreeDifferences.h"
#include "AI/AIControllerBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Tasks/AITask_MoveTo.h"
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


void AEnemyBase::GetInCombat(AActor* TargetActor)
{
	FAIMoveRequest AIMoveRequest;
	AIMoveRequest.SetGoalActor(TargetActor);
	AIController->MoveTo(AIMoveRequest);
}

void AEnemyBase::ChasePlayer()
{
}

void AEnemyBase::Attack()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance) return;
}
