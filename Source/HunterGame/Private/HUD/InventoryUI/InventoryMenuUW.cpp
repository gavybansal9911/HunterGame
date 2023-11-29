// Hunter Game by Gamer Guru.


#include "HUD/InventoryUI/InventoryMenuUW.h"
#include "HUD/HunterHUD.h"
#include "HUD/InventoryUI/InventoryGridUW.h"

UInventoryMenuUW::UInventoryMenuUW()
{
	SetIsFocusable(true);
}

void UInventoryMenuUW::NativeConstruct()
{
	Super::NativeConstruct();
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
