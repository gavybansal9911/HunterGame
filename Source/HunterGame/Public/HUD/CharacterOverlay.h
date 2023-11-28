// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterOverlay.generated.h"

class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class HUNTERGAME_API UCharacterOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	void OnCombatEnabled();
	void OnCombatDisabled();
	
public:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* HealthText;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* AmmoText;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* WeaponAmmoAmountText;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* AmmoInInventoryText;
};
