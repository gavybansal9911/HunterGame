// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTMoveToLocation.generated.h"

namespace EPathFollowingResult
{
	enum Type : int;
}

/**
 * 
 */
UCLASS(Blueprintable)
class HUNTERGAME_API UBTTMoveToLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    UFUNCTION()
	void OnMoveToLocationCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);
	
	UPROPERTY(EditAnywhere, Category = "BB")
	FName BB_PointOfInterest_KeyName;

private:
	TObjectPtr<AAIController> OwnerAIController;
};
