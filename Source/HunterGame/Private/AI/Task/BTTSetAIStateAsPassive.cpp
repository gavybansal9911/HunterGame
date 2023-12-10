// Hunter Game by Gamer Guru.


#include "AI/Task/BTTSetAIStateAsPassive.h"
#include "AI/AIControllerBase.h"

EBTNodeResult::Type UBTTSetAIStateAsPassive::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIControllerBase* AIEnemyController = Cast<AAIControllerBase>(OwnerComp.GetAIOwner()))
	{
		AIEnemyController->SetStateAsPassive();
	}
	
	return EBTNodeResult::Succeeded;
}
