// Hunter Game by Gamer Guru.


#include "HUD/InventoryUI/InventorySlotUW.h"
#include "Components/SizeBox.h"

void UInventorySlotUW::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (SlotSizeBox)
	{
		SlotSizeBox->SetWidthOverride(100.f);
		SlotSizeBox->SetHeightOverride(100.f);
	}
}

void UInventorySlotUW::NativeConstruct()
{
	Super::NativeConstruct();
}
