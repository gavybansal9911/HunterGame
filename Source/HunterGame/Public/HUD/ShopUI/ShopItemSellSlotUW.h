// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Component/InventoryTypes.h"
#include "HUD/UserWidgetBase.h"
#include "ShopItemSellSlotUW.generated.h"

class UButton;
class USizeBox;
class ABaseCharacter;

/**
 * 
 */
UCLASS()
class HUNTERGAME_API UShopItemSellSlotUW : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
	bool CanBuyItem();
	void BuyItem();
	
	/** Widget CallBacks **/
	void BindCallBacks();

	UFUNCTION()
	void OnSlotButtonClicked();
	/** Widget CallBacks **/
	
	void Init_ItemData(FItemData Data);

	// Player Character Reference
	UPROPERTY()
	ABaseCharacter* PlayerCharacter;
	
	/** Widget Components **/
	UPROPERTY(meta=(BindWidget))
	USizeBox* SlotSizeBox;

	UPROPERTY(meta=(BindWidget))
	UButton* SlotButton;
	/** Widget Components **/

private:
	FItemData ItemData;
};
