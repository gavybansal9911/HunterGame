// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryItemInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInventoryItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HUNTERGAME_API IInventoryItemInterface
{
	GENERATED_BODY()

public:
	virtual void UseItem();
	virtual void DropItem();
};
