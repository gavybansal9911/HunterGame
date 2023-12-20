// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "InventoryTypes.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class ABaseCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUNTERGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	friend ABaseCharacter;
	UInventoryComponent();

	// On Inventory Update Delegate
	FOnInventoryUpdated OnInventoryUpdated;
	
	/** Inventory Actions **/
	bool SpaceAvailable(FItemData ItemData);
	int32 AddItemToInventory(FItemData ItemToAddData);      // Return Value => (int32) Number of items left (unable to add)
	bool FindExistingSlot(FItemData ItemToAddData, int32& Index);     // Return Value => (bool) Existing slot available ? <---> // Args => Index passed by reference set value as ExistingSlotIndex if existing slot found and -1 if not
	bool FindEmptySlot(int32& Index);        // Return Value => (bool) Empty slot available ? <---> // Args => Index passed by reference set value as EmptySlotIndex if empty slot found and -1 if not
	int32 AddItemToExistingSlot(FItemData ItemToAddData, int32 ExistingSlotIndex);      // Return Value => (int32) NumberOfElementRemaining, returns -1 in case of a error <---> Args => ItemToAddData and ExistingSlotIndex
	int32 CreateNewStack(FItemData ItemToAddData, int32 NewStackIndex);       // Return Value => (int32) => NumberOfElementsRemaining, returns -1 in case of a error <---> Args => ItemToAddData and NewStackIndex
	int32 RemoveItemFromSlot(int32 SlotIndex, int32 NumberOfElementsToRemove);           // Return Value => (bool) => Number of elements removed ? <---> Args => SlotIndex and NumberOfElementsToRemove
	void CleanSlot(int32 SlotIndex);
	/** Inventory Actions **/

protected:
	virtual void BeginPlay() override;

	/** Inventory Properties **/
	UPROPERTY(EditAnywhere, Category = "Properties")
	int32 NumberOfSlots = 0;
	/** Inventory Properties **/

private:
	void InitInventory();
	
	TArray<FSlotData> Content;

public:
	FORCEINLINE TArray<FSlotData> GetContent() const {return Content;}
	FORCEINLINE int32 GetNumberOfSlots() const {return NumberOfSlots;}
};
