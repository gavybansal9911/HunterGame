// Hunter Game by Gamer Guru.


#include "AI/Task/BTTGetRandomLocationInArea.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTGetRandomLocationInArea::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent())
	{
		FVector Origin = OwnerComp .GetAIOwner()->GetPawn()->GetActorLocation();
		FVector Local_PointOfInterest;
		UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(GetWorld(), Origin,
			Local_PointOfInterest, NavigableAreaRadius);

		BlackboardComponent->SetValueAsVector(BB_PointOfInterest_KeyName, Local_PointOfInterest);

		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
