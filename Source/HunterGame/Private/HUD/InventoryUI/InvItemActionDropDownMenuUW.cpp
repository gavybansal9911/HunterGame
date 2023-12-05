// Hunter Game by Gamer Guru.


#include "HUD/InventoryUI/InvItemActionDropDownMenuUW.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "HUD/InventoryUI/InventoryMenuUW.h"

void UInvItemActionDropDownMenuUW::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UInvItemActionDropDownMenuUW::NativeConstruct()
{
	Super::NativeConstruct();
	BindWidgetCallBacks();
}

void UInvItemActionDropDownMenuUW::Initialize(FWidgetTransform WidgetTransform)
{
	SetRenderTransform(WidgetTransform);
}

void UInvItemActionDropDownMenuUW::BindWidgetCallBacks()
{
	if (UseButton)
		{UseButton->OnClicked.AddDynamic(this, &UInvItemActionDropDownMenuUW::OnUseButtonPressed);}
	
	if (DropButton)
		{UseButton->OnClicked.AddDynamic(this, &UInvItemActionDropDownMenuUW::OnDropButtonPressed);}
}

void UInvItemActionDropDownMenuUW::OnUseButtonPressed()
{
}

void UInvItemActionDropDownMenuUW::OnDropButtonPressed()
{
}
