// Hunter Game by Gamer Guru.


#include "AI/Task/BTTGetRandomLocationInArea.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTGetRandomLocationInArea::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GET_NEW_POINT:
	if (UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent())
	{
		FVector Origin = OwnerComp .GetAIOwner()->GetPawn()->GetActorLocation();
		FVector Local_PointOfInterest;
		UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(GetWorld(), Origin,
			Local_PointOfInterest, NavigableAreaRadius);

		if (OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation().Size() - Local_PointOfInterest.Size() < 150.f)
		{
			goto GET_NEW_POINT;
		}

		BlackboardComponent->SetValueAsVector(BB_PointOfInterest_KeyName, Local_PointOfInterest);

		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
