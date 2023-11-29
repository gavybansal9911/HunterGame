// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "HUD/UserWidgetBase.h"
#include "InventoryMenuUW.generated.h"

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
	
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn))
	UInventoryComponent* InventoryComponent;

private:
	UPROPERTY()
	AHunterHUD* OwnerHUD;

public:
	FORCEINLINE void SetOwnerHUD(AHunterHUD* InHUD) {OwnerHUD = InHUD;}
};
