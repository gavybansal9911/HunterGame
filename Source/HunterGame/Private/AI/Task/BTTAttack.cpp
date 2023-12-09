// Hunter Game by Gamer Guru.


#include "AI/Task/BTTAttack.h"
#include "AIController.h"
#include "AI/EnemyBase.h"

EBTNodeResult::Type UBTTAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AEnemyBase* AIEnemyCharacter = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		AIEnemyCharacter->Attack();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
