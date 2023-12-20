// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Component/InventoryTypes.h"
#include "HUD/UserWidgetBase.h"
#include "ShopMenu.generated.h"

class UShopItemSellSlotUW;
class UWidgetSwitcher;
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

	void Init_Content(TArray<FItemData> Content);
	void Init_BuyTab();
	void Init_SellTab();
	void OnBuyTabClosed();
	void OnSellTabClosed();
	
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

	UPROPERTY(meta=(BindWidget))
	UWidgetSwitcher* MenuSwitcher;
	/** Widget Components **/

protected:
	UPROPERTY(EditAnywhere, Category = "Properties")
	TSubclassOf<UShopItemSellSlotUW> ShopItemSellSlotUW_Class;;
	
private:
	TArray<FItemData> ShopContent;
};
