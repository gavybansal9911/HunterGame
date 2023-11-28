// Hunter Game by Gamer Guru.


#include "PlayerController/HunterPlayerController.h"
#include "HUD/HunterHUD.h"
#include "HUD/CharacterOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void AHunterPlayerController::BeginPlay()
{
	Super::BeginPlay();
	HunterHUD = Cast<AHunterHUD>(GetHUD());
}

void AHunterPlayerController::SetHUDHealth(float Health, float MaxHealth)
{
	HunterHUD = HunterHUD == nullptr ? Cast<AHunterHUD>(GetHUD()) : HunterHUD;

	if (HunterHUD && HunterHUD->CharacterOverlay && HunterHUD->CharacterOverlay->HealthBar && HunterHUD->CharacterOverlay->HealthText)
	{
		const float HealthPercent = Health / MaxHealth;

		HunterHUD->CharacterOverlay->HealthBar->SetPercent(HealthPercent);
		const FString HealthText = FString::Printf(TEXT("%d/%d"), FMath::CeilToInt(Health), FMath::CeilToInt(MaxHealth));
		HunterHUD->CharacterOverlay->HealthText->SetText(FText::FromString(HealthText));
	}
}

void AHunterPlayerController::SetHUDWeaponAmmo(int32 InWeaponAmmoAmount, int32 InInventoryAmmoAmount)
{
	HunterHUD = HunterHUD == nullptr ? Cast<AHunterHUD>(GetHUD()) : HunterHUD;

	if (HunterHUD && HunterHUD->CharacterOverlay && HunterHUD->CharacterOverlay->WeaponAmmoAmountText && HunterHUD->CharacterOverlay->AmmoInInventoryText)
	{
		const FString InWeapon_Text = FString::Printf(TEXT("%d"), InWeaponAmmoAmount);
		HunterHUD->CharacterOverlay->WeaponAmmoAmountText->SetText(FText::FromString(InWeapon_Text));

		const FString InInventory_Text = FString::Printf(TEXT("%d"), InInventoryAmmoAmount);
		HunterHUD->CharacterOverlay->AmmoInInventoryText->SetText(FText::FromString(InInventory_Text));
	}
}
