// Hunter Game by Gamer Guru.


#include "AI/Decorator/BTDShouldRunAway.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTDShouldRunAway::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (OwnerComp.GetBlackboardComponent() == nullptr) return false;
	if (OwnerComp.GetAIOwner() == nullptr || OwnerComp.GetAIOwner()->GetPawn() == nullptr) return false;


	if (const AActor* Actor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(RunAwayFromActor_BB_KeyName)))
	{
		if (OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation().Size() - Actor->GetActorLocation().Size() > RunAwayMinRange)
		{
			return true;
		}
	}

	return false;
}
