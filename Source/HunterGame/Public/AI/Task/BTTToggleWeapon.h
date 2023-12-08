// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTToggleWeapon.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class HUNTERGAME_API UBTTToggleWeapon : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
