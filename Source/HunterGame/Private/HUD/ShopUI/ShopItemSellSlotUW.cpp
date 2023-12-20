// Hunter Game by Gamer Guru.


#include "HUD/ShopUI/ShopItemSellSlotUW.h"
#include "Components/Button.h"

void UShopItemSellSlotUW::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UShopItemSellSlotUW::NativeConstruct()
{
	Super::NativeConstruct();
	BindCallBacks();
}

void UShopItemSellSlotUW::BindCallBacks()
{
	if (SlotButton)
		{SlotButton->OnClicked.AddDynamic(this, &UShopItemSellSlotUW::OnSlotButtonClicked);}
}

void UShopItemSellSlotUW::Init_ItemData(FItemData Data)
{
	ItemData = Data;
}

void UShopItemSellSlotUW::OnSlotButtonClicked()
{
	// TODO: Implementation
}
