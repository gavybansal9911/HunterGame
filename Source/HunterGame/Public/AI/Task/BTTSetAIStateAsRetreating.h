// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTSetAIStateAsRetreating.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class HUNTERGAME_API UBTTSetAIStateAsRetreating : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
