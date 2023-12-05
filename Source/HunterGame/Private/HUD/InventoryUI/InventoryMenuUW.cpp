// Hunter Game by Gamer Guru.


#include "HUD/InventoryUI/InventoryMenuUW.h"
#include "Components/Button.h"
#include "HUD/HunterHUD.h"
#include "HUD/InventoryUI/InventoryGridUW.h"
#include "HUD/InventoryUI/InventorySlotUW.h"
#include "HUD/InventoryUI/InvItemActionDropDownMenuUW.h"

UInventoryMenuUW::UInventoryMenuUW()
{
	SetIsFocusable(true);
}

void UInventoryMenuUW::NativeConstruct()
{
	Super::NativeConstruct();
	BindCallBacks();
	if (InventoryGrid)
	{
		InventoryGrid->InventorySlotUWClass = InventorySlotClass;
		InventoryGrid->MakeSlots();
	}
}

void UInventoryMenuUW::NativeDestruct()
{
	Super::NativeDestruct();

	if (InventoryGrid)
	{
		for (UInventorySlotUW* ItemSlot : InventoryGrid->InventorySlots)
		{
			if (ItemSlot)
			{
				if (ItemSlot->DropDownMenuUW)
				{
					ItemSlot->DropDownMenuUW = nullptr;
				}
				ItemSlot = nullptr;
			}
		}
	}
}

FReply UInventoryMenuUW::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (!OwnerHUD) return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
	
	if (InKeyEvent.GetKey() == EKeys::I || InKeyEvent.GetKey() == EKeys::BackSpace)
	{
		OwnerHUD->SetInputModeAsGameOnly();
		OwnerHUD->ToggleInventory();
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

FReply UInventoryMenuUW::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		CloseItemSlotDropDownMenus();
	}
	
	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

void UInventoryMenuUW::BindCallBacks()
{
	if (CloseInventoryMenuButton)
		{CloseInventoryMenuButton->OnClicked.AddDynamic(this, &UInventoryMenuUW::OnCloseInventoryMenuButtonClicked);}
}

void UInventoryMenuUW::OnCloseInventoryMenuButtonClicked()
{
	if (!OwnerHUD) return;
	CloseItemSlotDropDownMenus();
	OwnerHUD->SetInputModeAsGameOnly();
	OwnerHUD->ToggleInventory();
}

void UInventoryMenuUW::CloseItemSlotDropDownMenus()
{
	if (InventoryGrid)
	{
		for (UInventorySlotUW* ItemSlot : InventoryGrid->InventorySlots)
		{
			if (ItemSlot)
			{
				if (ItemSlot->DropDownMenuUW)
				{
					ItemSlot->DropDownMenuUW->RemoveFromParent();
					ItemSlot->DropDownMenuUW = nullptr;
				}
			}
		}
	}
}
