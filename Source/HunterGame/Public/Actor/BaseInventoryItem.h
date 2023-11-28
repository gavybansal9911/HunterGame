// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Actor/BaseItemActor.h"
#include "Component/InventoryTypes.h"
#include "Interface/InventoryItemInterface.h"
#include "BaseInventoryItem.generated.h"

/**
 * 
 */
UCLASS()
class HUNTERGAME_API ABaseInventoryItem : public ABaseItemActor, public IInventoryItemInterface
{
	GENERATED_BODY()

public:
	ABaseInventoryItem();

	/** Interface **/
	virtual void InteractWith(ABaseCharacter* PlayerCharacter) override;   // IInteractInterface
	virtual void UseItem() override;                                       // IInventoryItemInterface
	virtual void DropItem() override;                                      // IInventoryItemInterface
	/** Interface **/

protected:
	virtual void BeginPlay() override;
	
	// Item Data
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Data")
	FItemData ItemData;
};
