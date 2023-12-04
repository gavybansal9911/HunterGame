// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Component/InventoryTypes.h"
#include "HUD/UserWidgetBase.h"
#include "InventorySlotUW.generated.h"

class UInvItemActionDropDownMenuUW;
class UTextBlock;
class UImage;
class UButton;
class USizeBox;

/**
 * 
 */
UCLASS()
class HUNTERGAME_API UInventorySlotUW : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	// On Slot Data Set
	void SlotDataSet();

	// Set Slot Properties
	void SetSlotProperties();
	
	// Slot Data
	FSlotData SlotData;
	
	/** Widget CallBacks **/
	void BindWidgetCallBacks();

	UFUNCTION()
	void OnSlotButtonPressed();
	/** Widget CallBacks **/
	
	/** Widget Components **/
	UPROPERTY(meta=(BindWidget))
	USizeBox* SlotSizeBox;

	UPROPERTY(meta=(BindWidget))
	UButton* SlotButton;

	UPROPERTY(meta=(BindWidget))
	UImage* IconTexture;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* QuantityText;
	/** Widget Components **/

	// Drop Down Menu Class
	UPROPERTY(EditAnywhere, Category = "Drop Down Menu")
	TSubclassOf<UInvItemActionDropDownMenuUW> DropDownMenuUWClass;
	
	// Drop Down Menu
	UPROPERTY()
	UInvItemActionDropDownMenuUW* DropDownMenuUW;

	/** Other Variables **/
	UPROPERTY(EditAnywhere, Category = "Properties")
	UTexture2D* EmptySlotTexture;
	/** Other Variables **/
};
