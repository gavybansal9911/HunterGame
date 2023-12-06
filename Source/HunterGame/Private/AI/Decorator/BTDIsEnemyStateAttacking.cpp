// Hunter Game by Gamer Guru.


#include "AI/Decorator/BTDIsEnemyStateAttacking.h"
#include "AIController.h"
#include "AI/EnemyBase.h"
#include "AI/AI_Types.h"

bool UBTDIsEnemyStateAttacking::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* AIOwnerController = OwnerComp.GetAIOwner();

	if (AIOwnerController)
	{
		if (AEnemyBase* EnemyCharacter = Cast<AEnemyBase>(AIOwnerController->GetPawn()))
		{
			return EnemyCharacter->GetEnemyState() == EAIState::EAIS_Attacking;
		}
	}
	
	return Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
}
