// Hunter Game by Gamer Guru.


#include "AI/Task/BTTSetAIStateAsRunningAway.h"
#include "AI/AIControllerBase.h"

EBTNodeResult::Type UBTTSetAIStateAsRunningAway::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIControllerBase* AIEnemyController = Cast<AAIControllerBase>(OwnerComp.GetAIOwner()))
	{
		AIEnemyController->SetStateAsRunningAway();
	}
	
	return EBTNodeResult::Succeeded;
}
