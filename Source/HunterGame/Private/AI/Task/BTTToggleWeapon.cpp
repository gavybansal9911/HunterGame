// Hunter Game by Gamer Guru.


#include "AI/Task/BTTToggleWeapon.h"
#include "AIController.h"
#include "AI/EnemyBase.h"

EBTNodeResult::Type UBTTToggleWeapon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AEnemyBase* AIEnemyBaseCharacter = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		const bool bSuccess = AIEnemyBaseCharacter->ToggleWeapon();
		if (bSuccess)
			return EBTNodeResult::Succeeded;
		else
			return EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::Failed;
}
