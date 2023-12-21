// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTGetLocAroundLeader_Animal.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class HUNTERGAME_API UBTTGetLocAroundLeader_Animal : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "BB")
	FName BB_PointOfInterest_KeyName = "PointOfInterest";
	
	UPROPERTY(EditAnywhere, Category = "Task Input")
	float NavigableAreaRadius = 2000.f;
};
