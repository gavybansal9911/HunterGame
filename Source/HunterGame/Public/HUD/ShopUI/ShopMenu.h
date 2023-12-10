// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "HUD/UserWidgetBase.h"
#include "ShopMenu.generated.h"

class UScrollBox;
class UHorizontalBox;
class UVerticalBox;
class UCanvasPanel;
class ABaseCharacter;
class UButton;
/**
 * 
 */
UCLASS()
class HUNTERGAME_API UShopMenu : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	// Player Character Reference
	UPROPERTY()
	ABaseCharacter* PlayerCharacter;
	
	/** Widget CallBacks **/
	void BindCallBacks();
	
	UFUNCTION()
	void OnCloseShopMenuButtonClicked();
	
	UFUNCTION()
	void OnOpenSellTabButtonClicked();
	
	UFUNCTION()
	void OnOpenPurchaseTabButtonClicked();
	/** Widget CallBacks **/
	
	/** Widget Components **/
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* ShopMenuCanvasPanel;

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* ShopMenuVerticalBox;

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* SwitchTabHorizontalBox;

	UPROPERTY(meta=(BindWidget))
	UButton* OpenSellTabButton;

	UPROPERTY(meta=(BindWidget))
	UButton* OpenPurchaseTabButton;
	
	UPROPERTY(meta=(BindWidget))
	UButton* CloseShopMenuButton;

	UPROPERTY(meta=(BindWidget))
	UScrollBox* SellTabScrollBox;

	UPROPERTY(meta=(BindWidget))
	UScrollBox* PurchaseTabScrollBox;
	/** Widget Components **/
};
