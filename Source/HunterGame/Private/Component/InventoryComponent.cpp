// Hunter Game by Gamer Guru.


#include "Component/InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::InitInventory()
{
	Content.SetNum(NumberOfSlots);
}

int32 UInventoryComponent::AddItemToInventory(FItemData ItemToAddData)
{
	int32 ExistingSlotIndex;
	if (FindExistingSlot(ItemToAddData, ExistingSlotIndex))
	{
		const int32 Local_ElementsRemaining = AddItemToExistingSlot(ItemToAddData, ExistingSlotIndex);
		if (Local_ElementsRemaining > 0)
		{
			ItemToAddData.NumberOfElements = Local_ElementsRemaining;
			OnInventoryUpdated.Broadcast();  // Trigger OnInventoryUpdated delegate
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
				ItemToAddData.NumberOfElements = Local_ElementsRemaining;
				OnInventoryUpdated.Broadcast();  // Trigger OnInventoryUpdated delegate
				return Local_ElementsRemaining;
			}
		}
		
		else
		{
			return -1;
		}
	}
	OnInventoryUpdated.Broadcast();  // Trigger OnInventoryUpdated delegate
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

int32 UInventoryComponent::RemoveItemFromSlot(int32 SlotIndex, int32 NumberOfElementsToRemove)
{
	int32 Local_NumberOfElementsToBeRemoved = NumberOfElementsToRemove;
	
	if (NumberOfElementsToRemove > Content[SlotIndex].Quantity)
	{
		Local_NumberOfElementsToBeRemoved = Content[SlotIndex].Quantity;
		Content[SlotIndex].Quantity = 0;
		CleanSlot(SlotIndex);
		OnInventoryUpdated.Broadcast();
		return Local_NumberOfElementsToBeRemoved;
	}
	else
	{
		Content[SlotIndex].Quantity = Content[SlotIndex].Quantity - NumberOfElementsToRemove;
		if (Content[SlotIndex].Quantity == 0)
		{
			CleanSlot(SlotIndex);
		}
		OnInventoryUpdated.Broadcast();
		return Local_NumberOfElementsToBeRemoved;
	}
}

void UInventoryComponent::CleanSlot(int32 SlotIndex)
{
	Content[SlotIndex].ItemID = FString();
	Content[SlotIndex].ItemID = FString();
	Content[SlotIndex].ItemData.ItemID = FString();
	Content[SlotIndex].ItemData.ItemName = FName();
	Content[SlotIndex].ItemData.ItemClass = nullptr;
}
