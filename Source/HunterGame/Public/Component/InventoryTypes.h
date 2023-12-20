#pragma once

#include "CoreMinimal.h"
#include "InventoryTypes.generated.h"

class ABaseInventoryItem;

UENUM(BlueprintType)
enum EItemClassification : uint8
{
	EIC_Weapon UMETA(DisplayName = Weapon),
	EIC_Accessories UMETA(DisplayName = Accessories)
};

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	FItemData() {}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EItemClassification ItemClassification;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Cost;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 NumberOfElements = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxStackSize = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ABaseInventoryItem> ItemClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bUsable = true;
};

USTRUCT(BlueprintType)
struct FSlotData
{
	GENERATED_BODY()

	FSlotData() {}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString ItemID = FString();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Quantity = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FItemData ItemData = FItemData();
};
