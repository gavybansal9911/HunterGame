// Hunter Game by Gamer Guru.


#include "AI/Decorator/BTDIsEnemyStateHunting.h"
#include "AIController.h"
#include "AI/AI_Types.h"
#include "AI/EnemyBase.h"

bool UBTDIsEnemyStateHunting::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* AIOwnerController = OwnerComp.GetAIOwner();

	if (AIOwnerController)
	{
		if (AEnemyBase* EnemyCharacter = Cast<AEnemyBase>(AIOwnerController->GetPawn()))
		{
			return EnemyCharacter->GetEnemyState() == EAIState::EAIS_Hunting;
		}
	}
	
	return false;
}
