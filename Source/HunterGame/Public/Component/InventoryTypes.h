#pragma once

#include "CoreMinimal.h"
#include "InventoryTypes.generated.h"

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	FItemData() {}

	UPROPERTY(EditDefaultsOnly)
	FString ItemID = FString();

	UPROPERTY(EditDefaultsOnly)
	FName ItemName = FName();

	UPROPERTY(EditDefaultsOnly)
	FString Description = FString();

	UPROPERTY(EditDefaultsOnly)
	int32 NumberOfElements = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxStackSize = 0;
};

USTRUCT(BlueprintType)
struct FSlotData
{
	GENERATED_BODY()

	FSlotData() {}

	UPROPERTY(EditDefaultsOnly)
	FString ItemID = FString();

	UPROPERTY(EditDefaultsOnly)
	int32 Quantity = 0;
	
	UPROPERTY(EditDefaultsOnly)
	FItemData ItemData = FItemData();
};
