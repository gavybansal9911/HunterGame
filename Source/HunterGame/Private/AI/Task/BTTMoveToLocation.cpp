// Hunter Game by Gamer Guru.


#include "AI/Task/BTTMoveToLocation.h"
#include "AIController.h"
#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"

EBTNodeResult::Type UBTTMoveToLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent())
	{
		if (AAIController* AIController = OwnerComp.GetAIOwner())
		{
			OwnerAIController = AIController;

			FVector Local_PointOfInterest = BlackboardComponent->GetValueAsVector(BB_PointOfInterest_KeyName);
			AIController->MoveToLocation(Local_PointOfInterest, 10.f, true, true);
			AIController->ReceiveMoveCompleted.AddDynamic(this, &UBTTMoveToLocation::OnMoveToLocationCompleted);
			
			return EBTNodeResult::InProgress;
		}
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTMoveToLocation::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//if (AController* OwnerController = Cast<AController>(OwnerComp.GetAIOwner()))
	//if (OwnerAIController)
	//{
		//FNavigationSystem::StopMovement(*OwnerAIController);
		//return EBTNodeResult::Aborted;   // TODO: /____/
	//}	

	return EBTNodeResult::Succeeded;
}

void UBTTMoveToLocation::OnMoveToLocationCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	UBehaviorTreeComponent* OwnerComp = Cast<UBehaviorTreeComponent>(OwnerAIController->BrainComponent);
	if (OwnerComp == nullptr)
	{
		FinishLatentTask(*OwnerComp, EBTNodeResult::Failed);
		return;
	}
	
	if (Result == EPathFollowingResult::Success)
	{
		FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	else
	{
		FinishLatentTask(*OwnerComp, EBTNodeResult::Failed);
		return;
	}
}
