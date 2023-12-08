// Hunter Game by Gamer Guru.


#include "AI/Task/BTTToggleWeapon.h"

#include "AIController.h"
#include "AI/EnemyBase.h"

EBTNodeResult::Type UBTTToggleWeapon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AEnemyBase* AIEnemyBaseCharacter = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		AIEnemyBaseCharacter->ToggleWeapon();
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
