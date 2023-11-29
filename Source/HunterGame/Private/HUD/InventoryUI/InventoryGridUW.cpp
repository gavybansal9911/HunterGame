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

	int Local_Row = 0;
	int Local_Column = 0;
	const int Local_NumberOfSlots = InventoryComponent->GetNumberOfSlots();
	for (int i = 0; i < Local_NumberOfSlots; i++)
	{
		if (Local_Column > NumberOfColumns)
		{
			Local_Column = 0;
			Local_Row++;
		}
		
		UInventorySlotUW* InventorySlot = CreateWidget<UInventorySlotUW>(this, UInventorySlotUW::StaticClass());
		InventoryGridPanel->AddChildToGrid(InventorySlot, Local_Row, Local_Column);
		Local_Column++;
	}
}
