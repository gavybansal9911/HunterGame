// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "HUD/UserWidgetBase.h"
#include "InventorySlotUW.generated.h"

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

	/** Widget Components **/
	UPROPERTY(meta=(BindWidget))
	USizeBox* SlotSizeBox;
	/** Widget Components **/
};
