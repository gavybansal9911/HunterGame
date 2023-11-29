// Hunter Game by Gamer Guru.


#include "HUD/InventoryUI/InventoryGridUW.h"
#include "Component/InventoryComponent.h"
#include "Components/GridPanel.h"
#include "HUD/InventoryUI/InventorySlotUW.h"

void UInventoryGridUW::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UInventoryGridUW::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryGridUW::MakeSlots()
{
	if (InventoryComponent == nullptr || InventoryGridPanel == nullptr) return;

	const int Local_NumberOfSlots = InventoryComponent->GetNumberOfSlots();
	for (int i = 0; i < Local_NumberOfSlots; i++)
	{
		UInventorySlotUW* InventorySlot = CreateWidget<UInventorySlotUW>(this, UInventorySlotUW::StaticClass());
		InventoryGridPanel->AddChildToGrid(InventorySlot, 0, 0);
	}
}
