// Hunter Game by Gamer Guru.


#include "AI/Task/BTTChaseActor.h"
#include "AIController.h"
#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTChaseActor::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent())
	{
		if (AAIController* AIController = OwnerComp.GetAIOwner())
		{
			if (AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(BB_TargetActor_KeyName)))
			{
				AIController->MoveToActor(TargetActor, 10.f, false, true);

				return EBTNodeResult::Succeeded;
			}
		}
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTChaseActor::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AController* OwnerController = Cast<AController>(OwnerComp.GetAIOwner()))
	{
		FNavigationSystem::StopMovement(*OwnerController);
		return EBTNodeResult::Aborted;
	}	
	
	return Super::AbortTask(OwnerComp, NodeMemory);
}
