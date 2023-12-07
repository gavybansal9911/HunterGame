// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTCheckCanAttack.generated.h"

/**
 * 
 */
UCLASS()
class HUNTERGAME_API UBTTCheckCanAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
    EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "BB")
	FName BB_TargetActor_KeyName;
};
