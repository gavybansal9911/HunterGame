// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "HUD/UserWidgetBase.h"
#include "InventoryGridUW.generated.h"

class UGridPanel;
class USizeBox;
class UInventoryComponent;

/**
 * 
 */
UCLASS()
class HUNTERGAME_API UInventoryGridUW : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	void virtual NativePreConstruct() override;
	void virtual NativeConstruct() override;
	void MakeSlots();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn))
	UInventoryComponent* InventoryComponent;

	/** Widget Components **/
	UPROPERTY(meta=(BindWidget))
	USizeBox* InventoryGridSizeBox;

	UPROPERTY(meta=(BindWidget))
	UGridPanel* InventoryGridPanel;
	/** Widget Components **/
};
