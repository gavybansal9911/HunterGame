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
			AIController->MoveToLocation(Local_PointOfInterest, 250.f, false, true);
			AIController->ReceiveMoveCompleted.AddDynamic(this, &UBTTMoveToLocation::OnMoveToLocationCompleted);
			
			return EBTNodeResult::InProgress; 
		}
		else
		{
			//return EBTNodeResult::Failed;
			return EBTNodeResult::Succeeded;
		}
	}
	else
	{
		//return EBTNodeResult::Failed;
		return EBTNodeResult::Succeeded;
	}
}

EBTNodeResult::Type UBTTMoveToLocation::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//if (AController* OwnerController = Cast<AController>(OwnerComp.GetAIOwner()))
	//if (OwnerAIController)
	//{
		//FNavigationSystem::StopMovement(*OwnerAIController);
		//return EBTNodeResult::Aborted;   // TODO: /____/
	//}	

	//OwnerAIController->ReceiveMoveCompleted.RemoveDynamic(this, &UBTTMoveToLocation::OnMoveToLocationCompleted);
	return EBTNodeResult::Succeeded;
}

void UBTTMoveToLocation::OnMoveToLocationCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	//OwnerAIController->ReceiveMoveCompleted.RemoveDynamic(this, &UBTTMoveToLocation::OnMoveToLocationCompleted);
	
	if (OwnerAIController && OwnerAIController->BrainComponent)
	{
		UBehaviorTreeComponent* OwnerComp = Cast<UBehaviorTreeComponent>(OwnerAIController->BrainComponent);
		if (OwnerComp == nullptr)
		{
			FinishLatentTask(*OwnerComp, EBTNodeResult::Failed);
		}
		else if (Result == EPathFollowingResult::Success)
		{
			FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
		}
		else
		{
			FinishLatentTask(*OwnerComp, EBTNodeResult::Failed);
		}
	}
}
