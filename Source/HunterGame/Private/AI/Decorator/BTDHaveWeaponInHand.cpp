// Hunter Game by Gamer Guru.


#include "AI/Decorator/BTDHaveWeaponInHand.h"
#include "AIController.h"
#include "AI/EnemyBase.h"

bool UBTDHaveWeaponInHand::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (AEnemyBase* AIEnemyCharacter = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		return AIEnemyCharacter->HaveWeaponInHand();
	}
	
	return false;
}
