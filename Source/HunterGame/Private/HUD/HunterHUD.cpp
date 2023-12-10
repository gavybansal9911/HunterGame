// Hunter Game by Gamer Guru.


#include "HUD/HunterHUD.h"
#include "Character/BaseCharacter.h"
#include "GameFramework/PlayerController.h"
#include "HUD/CharacterOverlay.h"
#include "HUD/InventoryUI/InventoryMenuUW.h"

void AHunterHUD::BeginPlay()
{
	Super::BeginPlay();
	AddCharacterOverlay();
	if (ABaseCharacter* Character = Cast<ABaseCharacter>(GetOwningPawn()))
	{
		OwnerCharacter = Character;
	}
}

void AHunterHUD::AddCharacterOverlay()
{
	if (CharacterOverlay) return;
	
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

void AHunterHUD::SetInputModeAsUIOnly()
{
	if (!GetOwningPlayerController()) return;
	
	FInputModeUIOnly InputMode;
	GetOwningPlayerController()->SetInputMode(InputMode);
	GetOwningPlayerController()->SetShowMouseCursor(true);
}

void AHunterHUD::SetInputModeAsGameOnly()
{
	if (!GetOwningPlayerController()) return;
	
	FInputModeGameOnly InputMode;
	GetOwningPlayerController()->SetInputMode(InputMode);
	GetOwningPlayerController()->SetShowMouseCursor(false);
}

void AHunterHUD::HideCharacterOverlay()
{
	if (CharacterOverlay == nullptr) return;
	//CharacterOverlay->RemoveFromParent();
	CharacterOverlay->SetVisibility(ESlateVisibility::Hidden);
	//CharacterOverlay = nullptr;
}

void AHunterHUD::ShowCharacterOverlay()
{
	if (CharacterOverlay == nullptr) return;
	CharacterOverlay->SetVisibility(ESlateVisibility::Visible);
}

void AHunterHUD::OnCombatEnabled()
{
	if (CharacterOverlay == nullptr) return;
	CharacterOverlay->OnCombatEnabled();
}

void AHunterHUD::OnCombatDisabled()
{
	if (CharacterOverlay == nullptr) return;
	CharacterOverlay->OnCombatDisabled();
}

void AHunterHUD::ToggleInventory()
{
	if (!GetOwningPlayerController()) return;
	
	if (CharacterOverlay)
	{
		HideCharacterOverlay();
		InventoryMenu = CreateWidget<UInventoryMenuUW>(GetOwningPlayerController(), InventoryMenuClass);
		if (InventoryMenu)
		{
			if (OwnerCharacter && OwnerCharacter->InventoryComponent)
			{
				InventoryMenu->InventoryComponent = OwnerCharacter->InventoryComponent;
				InventoryMenu->SetOwnerHUD(this);
				InventoryMenu->AddToViewport();
			}
		}
		SetInputModeAsUIOnly();
	}
	else if (InventoryMenu)
	{
		InventoryMenu->RemoveFromParent();
		InventoryMenu->SetOwnerHUD(nullptr);
		InventoryMenu = nullptr;
		ShowCharacterOverlay();
		SetInputModeAsGameOnly();
	}
}
