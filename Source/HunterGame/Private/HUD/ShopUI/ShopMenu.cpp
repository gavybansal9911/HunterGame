// Hunter Game by Gamer Guru.


#include "HUD/ShopUI/ShopMenu.h"
#include "Character/BaseCharacter.h"
#include "Components/Button.h"
#include "HUD/HunterHUD.h"
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

void UShopMenu::BindCallBacks()
{
	if (CloseShopMenuButton)
	{
		CloseShopMenuButton->OnClicked.AddDynamic(this, &UShopMenu::OnCloseShopMenuButtonClicked);
	}
	if (OpenSellTabButton)
	{
		OpenSellTabButton->OnClicked.AddDynamic(this, &UShopMenu::OnOpenSellTabButtonClicked);
	}
	if (OpenPurchaseTabButton)
	{
		OpenPurchaseTabButton->OnClicked.AddDynamic(this, &UShopMenu::OnOpenPurchaseTabButtonClicked);
	}
}

void UShopMenu::OnCloseShopMenuButtonClicked()
{
	if (PlayerCharacter == nullptr) return;

	PlayerCharacter->ShowCharacterOverlayUI();
	if (PlayerCharacter->GetCustomPlayerController() && PlayerCharacter->GetCustomPlayerController()->GetHUDReference())
	{
		PlayerCharacter->GetCustomPlayerController()->GetHUDReference()->SetInputModeAsGameOnly();
	}
	RemoveFromParent();
}

void UShopMenu::OnOpenSellTabButtonClicked()
{
}

void UShopMenu::OnOpenPurchaseTabButtonClicked()
{
}
