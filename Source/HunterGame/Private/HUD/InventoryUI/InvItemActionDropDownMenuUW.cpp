// Hunter Game by Gamer Guru.


#include "HUD/InventoryUI/InvItemActionDropDownMenuUW.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/SizeBox.h"
#include "HUD/InventoryUI/InventorySlotUW.h"

void UInvItemActionDropDownMenuUW::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UInvItemActionDropDownMenuUW::NativeConstruct()
{
	Super::NativeConstruct();
	BindWidgetCallBacks();

	if (OwnerSlotUW)
	{
		if (OwnerSlotUW->SlotData.Quantity > 0)
		{
			if (OwnerSlotUW->SlotData.ItemData.bUsable == false && UseSizeBox)
			{
				UseSizeBox->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}
}

void UInvItemActionDropDownMenuUW::Init_Widget(FWidgetTransform WidgetTransform)
{
	SetRenderTransform(WidgetTransform);
}

void UInvItemActionDropDownMenuUW::BindWidgetCallBacks()
{
	if (UseButton)
		{UseButton->OnClicked.AddDynamic(this, &UInvItemActionDropDownMenuUW::OnUseButtonPressed);}
	
	if (DropButton)
		{DropButton->OnClicked.AddDynamic(this, &UInvItemActionDropDownMenuUW::OnDropButtonPressed);}
}

void UInvItemActionDropDownMenuUW::OnUseButtonPressed()
{
	GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Magenta, FString("Use Item"));
	RemoveFromParent();
}

void UInvItemActionDropDownMenuUW::OnDropButtonPressed()
{
	GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Magenta, FString("Drop Item"));
	RemoveFromParent();
}
