// Hunter Game by Gamer Guru.


#include "AI/Decorator/BTDIsEnemyStateChasing.h"
#include "AIController.h"
#include "AI/EnemyBase.h"
#include "AI/AI_Types.h"

bool UBTDIsEnemyStateChasing::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* AIOwnerController = OwnerComp.GetAIOwner();

	if (AIOwnerController)
	{
		if (AEnemyBase* EnemyCharacter = Cast<AEnemyBase>(AIOwnerController->GetPawn()))
		{
			return EnemyCharacter->GetEnemyState() == EAIState::EAIS_Chasing;
		}
	}
	
	return Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
}
