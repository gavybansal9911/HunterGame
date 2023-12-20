// Hunter Game by Gamer Guru.


#include "HUD/ShopUI/ShopMenu.h"
#include "Character/BaseCharacter.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"
#include "HUD/HunterHUD.h"
#include "HUD/ShopUI/ShopItemSellSlotUW.h"
#include "PlayerController/HunterPlayerController.h"

void UShopMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UShopMenu::NativeConstruct()
{
	Super::NativeConstruct();
	BindCallBacks();
}

void UShopMenu::Init_Content(TArray<FItemData> Content)
{
	ShopContent = Content;
}

void UShopMenu::Init_BuyTab()
{
	// TODO:
}

void UShopMenu::Init_SellTab()
{
	if (!ShopItemSellSlotUW_Class || !SellTabScrollBox) return;
	
	for (FItemData ItemData : ShopContent)
	{
		UShopItemSellSlotUW* ItemSellSlot = CreateWidget<UShopItemSellSlotUW>(GetWorld(), ShopItemSellSlotUW_Class);

		if (ItemSellSlot)
		{
			ItemSellSlot->Init_ItemData(ItemData);
			SellTabScrollBox->AddChild(ItemSellSlot);
		}
	}
}

void UShopMenu::OnBuyTabClosed()
{
	if (PurchaseTabScrollBox)
	{
		PurchaseTabScrollBox->ClearChildren();
	}
}

void UShopMenu::OnSellTabClosed()
{
	if (SellTabScrollBox)
	{
		SellTabScrollBox->ClearChildren();
	}
}

void UShopMenu::BindCallBacks()
{
	if (CloseShopMenuButton)
		{CloseShopMenuButton->OnClicked.AddDynamic(this, &UShopMenu::OnCloseShopMenuButtonClicked);}

	if (OpenSellTabButton)
		{OpenSellTabButton->OnClicked.AddDynamic(this, &UShopMenu::OnOpenSellTabButtonClicked);}

	if (OpenPurchaseTabButton)
		{OpenPurchaseTabButton->OnClicked.AddDynamic(this, &UShopMenu::OnOpenPurchaseTabButtonClicked);}
}

void UShopMenu::OnCloseShopMenuButtonClicked()
{
	if (PlayerCharacter == nullptr) return;

	// Closing Tabs
	OnBuyTabClosed();
	OnSellTabClosed();
	
	PlayerCharacter->ShowCharacterOverlayUI();
	if (PlayerCharacter->GetCustomPlayerController() && PlayerCharacter->GetCustomPlayerController()->GetHUDReference())
	{
		PlayerCharacter->GetCustomPlayerController()->GetHUDReference()->SetInputModeAsGameOnly();
		PlayerCharacter->GetCustomPlayerController()->SetViewTargetWithBlend(PlayerCharacter, 0.25f);
	}
	RemoveFromParent();
}

void UShopMenu::OnOpenPurchaseTabButtonClicked()
{
	if (MenuSwitcher)
	{
		MenuSwitcher->SetActiveWidgetIndex(0);
		OnSellTabClosed();
		Init_BuyTab();
	}
}

void UShopMenu::OnOpenSellTabButtonClicked()
{
	if (MenuSwitcher)
	{
		MenuSwitcher->SetActiveWidgetIndex(1);
		OnBuyTabClosed();
		Init_SellTab();
	}
}
