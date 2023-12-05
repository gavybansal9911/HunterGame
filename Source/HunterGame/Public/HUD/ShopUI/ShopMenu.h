// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "HUD/UserWidgetBase.h"
#include "ShopMenu.generated.h"

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
	/** Widget CallBacks **/
	
	/** Widget Components **/
	UPROPERTY(meta=(BindWidget))
	UButton* CloseShopMenuButton;
	/** Widget Components **/
};
