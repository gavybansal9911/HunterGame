#pragma once

#include "Stat_Types.generated.h"

USTRUCT(BlueprintType)
struct FAttributeData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Attribute")
	float BaseValue;
	UPROPERTY(EditAnywhere, Category = "Attribute")
	float CurrentValue;
};