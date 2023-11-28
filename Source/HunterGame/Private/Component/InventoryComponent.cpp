// Hunter Game by Gamer Guru.


#include "Component/InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::InitInventory()
{
	Content.SetNum(NumberOfSlots);
}

void UInventoryComponent::PrintContent()
{
	for (FSlotData Slot : Content)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Blue, FString::Printf(TEXT("%d"), Slot.Quantity));
	}
}

int32 UInventoryComponent::AddItemToInventory(FItemData ItemToAddData)
{
	int32 ExistingSlotIndex;
	if (FindExistingSlot(ItemToAddData, ExistingSlotIndex))
	{
		const int32 Local_ElementsRemaining = AddItemToExistingSlot(ItemToAddData, ExistingSlotIndex);
		if (Local_ElementsRemaining > 0)
		{
			// // TODO: Try to add remaining elements again
			ItemToAddData.NumberOfElements = Local_ElementsRemaining;
			//AddItemToInventory(ItemToAddData);
			return Local_ElementsRemaining;
		}
	}
	else
	{
		int32 EmptySlotIndex;
		if (FindEmptySlot(EmptySlotIndex))
		{
			const int32 Local_ElementsRemaining = CreateNewStack(ItemToAddData, EmptySlotIndex);
			if (Local_ElementsRemaining > 0)
			{
				// // TODO: Try to add remaining elements again
				ItemToAddData.NumberOfElements = Local_ElementsRemaining;
				//AddItemToInventory(ItemToAddData);
				return Local_ElementsRemaining;
			}
		}
		
		else
		{
			PrintContent();
			// TODO: Notify player that no space is available for the item
			return ItemToAddData.NumberOfElements;
		}
	}
	PrintContent();
	return 0;
}

bool UInventoryComponent::FindExistingSlot(FItemData ItemToAddData, int32& Index)
{
	bool Local_Success = false;
	int32 Local_Index = 0;
	
	for (FSlotData Slot : Content)
	{
		if (ItemToAddData.ItemName == Slot.ItemData.ItemName)
		{
			if (Slot.Quantity < Slot.ItemData.MaxStackSize)
			{
				Local_Success = true;
				Index = Local_Index;

				return Local_Success;
			}
		}
		
		Local_Index = Local_Index + 1;
	}

	Index = -1;
	return Local_Success;
}

bool UInventoryComponent::FindEmptySlot(int32& Index)
{
	bool Local_Success = false;
	int32 Local_Index = 0;
	
	for (FSlotData Slot : Content)
	{
		if (Slot.Quantity == 0)
		{
			Local_Success = true;
			Index = Local_Index;

			return Local_Success;
		}

		Local_Index = Local_Index + 1;
	}

	Index = -1;
	return Local_Success;
}

int32 UInventoryComponent::AddItemToExistingSlot(FItemData ItemToAddData, int32 ExistingSlotIndex)
{
	int32 NumberOfElementsRemaining = ItemToAddData.NumberOfElements;
	
	if (Content[ExistingSlotIndex].Quantity > ItemToAddData.MaxStackSize) return -1;

	while (ItemToAddData.NumberOfElements > 0 && Content[ExistingSlotIndex].Quantity < ItemToAddData.MaxStackSize)
	{
		Content[ExistingSlotIndex].Quantity++;
		ItemToAddData.NumberOfElements--;
		NumberOfElementsRemaining--;
	}

	return NumberOfElementsRemaining;
}

int32 UInventoryComponent::CreateNewStack(FItemData ItemToAddData, int32 NewStackIndex)
{
	if (Content[NewStackIndex].Quantity > 0) return -1;

	Content[NewStackIndex].ItemData = ItemToAddData;
	Content[NewStackIndex].ItemID = ItemToAddData.ItemID;
	if (ItemToAddData.NumberOfElements > ItemToAddData.MaxStackSize)
	{
		Content[NewStackIndex].Quantity = ItemToAddData.MaxStackSize;

		// Return the number of elements remaining
		return ItemToAddData.NumberOfElements - ItemToAddData.MaxStackSize;
	}
	else
	{
		Content[NewStackIndex].Quantity = ItemToAddData.NumberOfElements;
	}
	
	return 0;
}
