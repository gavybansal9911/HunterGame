// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDIsEnemyStateHunting.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class HUNTERGAME_API UBTDIsEnemyStateHunting : public UBTDecorator
{
	GENERATED_BODY()

public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
