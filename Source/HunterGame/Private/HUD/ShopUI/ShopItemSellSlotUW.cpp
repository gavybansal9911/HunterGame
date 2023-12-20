// Hunter Game by Gamer Guru.


#include "HUD/ShopUI/ShopItemSellSlotUW.h"

#include "Character/BaseCharacter.h"
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

bool UShopItemSellSlotUW::CanBuyItem()
{
	if (!PlayerCharacter) return false;
	return PlayerCharacter->CanBuyItem(ItemData);
}

void UShopItemSellSlotUW::BuyItem()
{
	PlayerCharacter->AddItemToInventory(ItemData);
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
	if (CanBuyItem())
	{
		BuyItem();
	}
}
