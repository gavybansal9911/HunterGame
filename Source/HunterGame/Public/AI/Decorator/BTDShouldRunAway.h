// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDShouldRunAway.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class HUNTERGAME_API UBTDShouldRunAway : public UBTDecorator
{
	GENERATED_BODY()

public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, Category = "BB")
	FName RunAwayFromActor_BB_KeyName = "TargetActor";

	UPROPERTY(EditAnywhere, Category = "BB Properties")
	float RunAwayMinRange = 5000.f;
};
