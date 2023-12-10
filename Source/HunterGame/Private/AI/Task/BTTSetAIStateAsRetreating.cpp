// Hunter Game by Gamer Guru.


#include "AI/Task/BTTSetAIStateAsRetreating.h"
#include "AI/AIControllerBase.h"

EBTNodeResult::Type UBTTSetAIStateAsRetreating::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIControllerBase* AIEnemyController = Cast<AAIControllerBase>(OwnerComp.GetAIOwner()))
	{
		AIEnemyController->SetStateAsRetreating();
	}
	
	return EBTNodeResult::Succeeded;
}
