// Hunter Game by Gamer Guru.


#include "HUD/InventoryUI/InventoryMenuUW.h"
#include "Components/Button.h"
#include "HUD/HunterHUD.h"
#include "HUD/InventoryUI/InventoryGridUW.h"

UInventoryMenuUW::UInventoryMenuUW()
{
	SetIsFocusable(true);
}

void UInventoryMenuUW::NativeConstruct()
{
	Super::NativeConstruct();
	BindCallBacks();
	if (InventoryGrid) {InventoryGrid->MakeSlots();}
}

FReply UInventoryMenuUW::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (!OwnerHUD) return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
	
	if (InKeyEvent.GetKey() == EKeys::I)
	{
		OwnerHUD->SetInputModeAsGameOnly();
		OwnerHUD->ToggleInventory();
	}

	// Pass the event to the parent class
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UInventoryMenuUW::BindCallBacks()
{
	if (CloseInventoryMenuButton)
	{
		CloseInventoryMenuButton->OnClicked.AddDynamic(this, &UInventoryMenuUW::OnCloseInventoryMenuButtonClicked);
	}
}

void UInventoryMenuUW::OnCloseInventoryMenuButtonClicked()
{
	if (!OwnerHUD) return;
	OwnerHUD->SetInputModeAsGameOnly();
	OwnerHUD->ToggleInventory();
}
