// Hunter Game by Gamer Guru.


#include "AI/Decorator/BTDIsEnemyStatePassive.h"
#include "AIController.h"
#include "AI/EnemyBase.h"

bool UBTDIsEnemyStatePassive::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* AIOwnerController = OwnerComp.GetAIOwner();

	if (AIOwnerController)
	{
		if (AEnemyBase* EnemyCharacter = Cast<AEnemyBase>(AIOwnerController->GetPawn()))
		{
			return EnemyCharacter->GetEnemyState() == EAIState::EAIS_Passive;
		}
	}
	
	return Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
}
