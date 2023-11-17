// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HunterHUD.generated.h"

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

private:
	// Function to draw crosshair
	void DrawCrosshair(UTexture2D* Texture, FVector2d ViewportCenter);

	// HUD Package struct variable
	FHUDPackage HUDPackage;

public:
	FORCEINLINE void SetHUDPackage(const FHUDPackage& InHUDPackage) {HUDPackage = InHUDPackage;}
};
