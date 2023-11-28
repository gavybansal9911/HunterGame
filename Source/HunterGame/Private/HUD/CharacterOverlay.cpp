// Hunter Game by Gamer Guru.


#include "HUD/CharacterOverlay.h"

#include "Components/TextBlock.h"

void UCharacterOverlay::OnCombatEnabled()
{
	if (!AmmoText) return;
	if (!WeaponAmmoAmountText) return;
	if (!AmmoInInventoryText) return;

	AmmoText->SetVisibility(ESlateVisibility::Visible);
	WeaponAmmoAmountText->SetVisibility(ESlateVisibility::Visible);
	AmmoInInventoryText->SetVisibility(ESlateVisibility::Visible);
}

void UCharacterOverlay::OnCombatDisabled()
{
	if (!AmmoText) return;
	if (!WeaponAmmoAmountText) return;
	if (!AmmoInInventoryText) return;

	AmmoText->SetVisibility(ESlateVisibility::Hidden);
	WeaponAmmoAmountText->SetVisibility(ESlateVisibility::Hidden);
	AmmoInInventoryText->SetVisibility(ESlateVisibility::Hidden);
}
