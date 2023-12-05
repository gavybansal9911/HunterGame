// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "HUD/UserWidgetBase.h"
#include "InventoryMenuUW.generated.h"

class UInventorySlotUW;
class UInventoryGridUW;
class UButton;
class AHunterHUD;
class UInventoryComponent;

/**
 * 
 */
UCLASS()
class HUNTERGAME_API UInventoryMenuUW : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	UInventoryMenuUW();
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	void BindCallBacks();
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn))
	UInventoryComponent* InventoryComponent;
	
	/** Widget Components **/
	UPROPERTY(meta=(BindWidget))
	UButton* CloseInventoryMenuButton;

	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UInventoryGridUW* InventoryGrid;
	/** Widget Components **/

protected:
	// Button CallBacks
	UFUNCTION()
	void OnCloseInventoryMenuButtonClicked();

	// References
	UPROPERTY(EditAnywhere, Category = "Slots")
	TSubclassOf<UInventorySlotUW> InventorySlotClass;
	
private:
	UPROPERTY()
	AHunterHUD* OwnerHUD;

	void CloseItemSlotDropDownMenus();

public:
	FORCEINLINE void SetOwnerHUD(AHunterHUD* InHUD) {OwnerHUD = InHUD;}
};
