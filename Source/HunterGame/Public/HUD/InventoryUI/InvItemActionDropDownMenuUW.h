// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "HUD/UserWidgetBase.h"
#include "InvItemActionDropDownMenuUW.generated.h"

class USizeBox;
class UButton;

/**
 * 
 */
UCLASS()
class HUNTERGAME_API UInvItemActionDropDownMenuUW : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	/** Widget CallBacks **/
	void BindWidgetCallBacks();
	void OnUseButtonPressed();
	void OnDropButtonPressed();
	/** Widget CallBacks **/
	
	/** Widget Components **/
	UPROPERTY(meta=(BindWidget))
	USizeBox* DropDownMenuSizeBox;

	UPROPERTY(meta=(BindWidget))
	USizeBox* UseSizeBox;
	
	UPROPERTY(meta=(BindWidget))
	USizeBox* DropSizeBox;

	UPROPERTY(meta=(BindWidget))
	UButton* UseButton;

	UPROPERTY(meta=(BindWidget))
	UButton* DropButton;
	/** Widget Components **/
};
