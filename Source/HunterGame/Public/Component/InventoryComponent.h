// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "InventoryTypes.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUNTERGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	friend ABaseCharacter;
	UInventoryComponent();

	/** Inventory Actions **/
	void PrintContent();
	int32 AddItemToInventory(FItemData ItemToAddData);      // Return Value => (int32) Number of items left (unable to add)
	bool FindExistingSlot(FItemData ItemToAddData, int32& Index);     // Return Value => (bool) Existing slot available ? <---> // Args => Index passed by reference set value as ExistingSlotIndex if existing slot found and -1 if not
	bool FindEmptySlot(int32& Index);        // Return Value => (bool) Empty slot available ? <---> // Args => Index passed by reference set value as EmptySlotIndex if empty slot found and -1 if not
	int32 AddItemToExistingSlot(FItemData ItemToAddData, int32 ExistingSlotIndex);      // Return Value => (int32) NumberOfElementRemaining, returns -1 in case of a error <---> Args => ItemToAddData and ExistingSlotIndex
	int32 CreateNewStack(FItemData ItemToAddData, int32 NewStackIndex);       // Return Value => (int32) => NumberOfElementsRemaining, returns -1 in case of a error <---> Args => ItemToAddData and NewStackIndex
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
};
