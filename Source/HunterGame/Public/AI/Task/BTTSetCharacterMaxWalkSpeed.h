// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTSetCharacterMaxWalkSpeed.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class HUNTERGAME_API UBTTSetCharacterMaxWalkSpeed : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Input")
	float NewMaxWalkSpeed;
};