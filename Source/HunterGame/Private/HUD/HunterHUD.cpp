// Hunter Game by Gamer Guru.


#include "HUD/HunterHUD.h"
#include "GameFramework/PlayerController.h"
#include "HUD/CharacterOverlay.h"

void AHunterHUD::BeginPlay()
{
	Super::BeginPlay();

	AddCharacterOverlay();
}

void AHunterHUD::AddCharacterOverlay()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController && CharacterOverlayClass)
	{
		CharacterOverlay = CreateWidget<UCharacterOverlay>(PlayerController, CharacterOverlayClass);
		if (CharacterOverlay) {CharacterOverlay->AddToViewport();}
	}
}

void AHunterHUD::DrawHUD()
{
	Super::DrawHUD();

	// Drawing Crosshair
	FVector2d ViewportSize;
	if (GEngine)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		const FVector2d ViewportCenter(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);

		float SpreadScaled = CrosshairSpreadMax * HUDPackage.CrosshairSpread;
		
		if (HUDPackage.CrosshairCenter)
		{
			FVector2d Spread(0.f, 0.f);
			DrawCrosshair(HUDPackage.CrosshairCenter, ViewportCenter, Spread);
		}
		if (HUDPackage.CrosshairLeft)
		{
			FVector2d Spread(-SpreadScaled, 0.f);
			DrawCrosshair(HUDPackage.CrosshairLeft, ViewportCenter, Spread);
		}
		if (HUDPackage.CrosshairRight)
		{
			FVector2d Spread(SpreadScaled, 0.f);
			DrawCrosshair(HUDPackage.CrosshairRight, ViewportCenter, Spread);
		}
		if (HUDPackage.CrosshairTop)
		{
			FVector2d Spread(0.f, -SpreadScaled);
			DrawCrosshair(HUDPackage.CrosshairTop, ViewportCenter, Spread);
		}
		if (HUDPackage.CrosshairBottom)
		{
			FVector2d Spread(0.f, SpreadScaled);
			DrawCrosshair(HUDPackage.CrosshairBottom, ViewportCenter, Spread);
		}
	}
}

void AHunterHUD::DrawCrosshair(UTexture2D* Texture, FVector2d ViewportCenter, FVector2d Spread)
{
	const float TextureWidth = Texture->GetSizeX();
	const float TextureHeight = Texture->GetSizeY();
	const FVector2d TextureDrawPoint(ViewportCenter.X - (TextureWidth / 2.f) + Spread.X,
		ViewportCenter.Y - (TextureHeight / 2.f) + Spread.Y);

	// Draw Texture
	DrawTexture(Texture, TextureDrawPoint.X, TextureDrawPoint.Y, TextureWidth, TextureHeight,
		0.f, 0.f, 1.f, 1.f, FLinearColor::White);
}
