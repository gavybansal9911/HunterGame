// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HunterHUD.generated.h"

class UInventoryMenuUW;
class UCharacterOverlay;
class UTexture2D;

USTRUCT(BlueprintType)
struct FHUDPackage
{
	GENERATED_BODY()

public:
	UTexture2D* CrosshairCenter;
	UTexture2D* CrosshairLeft;
	UTexture2D* CrosshairRight;	
	UTexture2D* CrosshairTop;
	UTexture2D* CrosshairBottom;
	float CrosshairSpread;    // Crosshair spread amount
};

/**
 * 
 */
UCLASS()
class HUNTERGAME_API AHunterHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;   // This function is called every frame
	
	void OnCombatEnabled();
	void OnCombatDisabled();
	void ToggleInventory();

	void SetInputModeAsUIOnly();
	void SetInputModeAsGameAndUI();
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> CharacterOverlayClass;
	UPROPERTY()
	UCharacterOverlay* CharacterOverlay;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> InventoryMenuClass;
	UPROPERTY()
	UInventoryMenuUW* InventoryMenu;

protected:
	virtual void BeginPlay() override;
	void AddCharacterOverlay();
	
private:
	// Function to draw crosshair
	void DrawCrosshair(UTexture2D* Texture, FVector2d ViewportCenter, FVector2d Spread);
	
	// HUD Package struct variable
	FHUDPackage HUDPackage;

	UPROPERTY(EditAnywhere, Category = "Crosshair")
	float CrosshairSpreadMax = 16.f;

public:
	FORCEINLINE void SetHUDPackage(const FHUDPackage& InHUDPackage) {HUDPackage = InHUDPackage;}
};
