// Hunter Game by Gamer Guru.


#include "HUD/ShopUI/ShopMenu.h"
#include "Character/BaseCharacter.h"
#include "Components/Button.h"

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
}

void UShopMenu::OnCloseShopMenuButtonClicked()
{
	if (PlayerCharacter == nullptr) return;

	PlayerCharacter->CreateCharacterOverlayUI();
	RemoveFromParent();
}
