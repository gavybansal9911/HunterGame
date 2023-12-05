// Hunter Game by Gamer Guru.


#include "HUD/InventoryUI/InventorySlotUW.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "HUD/InventoryUI/InvItemActionDropDownMenuUW.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UInventorySlotUW::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (SlotSizeBox)
	{
		SlotSizeBox->SetWidthOverride(100.f);
		SlotSizeBox->SetHeightOverride(100.f);
	}
}

void UInventorySlotUW::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventorySlotUW::SlotDataSet()
{
	SetSlotProperties();
	BindWidgetCallBacks();
}

void UInventorySlotUW::SetSlotProperties()
{
	if (SlotData.Quantity == 0)
	{
		SlotButton->SetIsEnabled(false);
		if (IconTexture && EmptySlotTexture && QuantityText)
		{
			IconTexture->SetBrushFromTexture(EmptySlotTexture);
			const FString Local_QuantityText = FString::Printf(TEXT("%d"), 0);
			QuantityText->SetText(FText::FromString(Local_QuantityText));
		}
	}
	else
	{
		SlotButton->SetIsEnabled(true);
		if (IconTexture && QuantityText && SlotData.ItemData.Icon)
		{
			IconTexture->SetBrushFromTexture(SlotData.ItemData.Icon);
			const FString Local_QuantityText = FString::Printf(TEXT("%d"), SlotData.Quantity);
			QuantityText->SetText(FText::FromString(Local_QuantityText));
		}
	}
}

void UInventorySlotUW::BindWidgetCallBacks()
{
	if (SlotButton)
	{
		SlotButton->OnClicked.AddDynamic(this, &UInventorySlotUW::OnSlotButtonPressed);
	}
}

void UInventorySlotUW::OnSlotButtonPressed()
{
	if (DropDownMenuUWClass == nullptr) return;

	if (DropDownMenuUW)
	{
		DropDownMenuUW->RemoveFromParent();
		DropDownMenuUW = nullptr;
	}
	
	DropDownMenuUW = CreateWidget<UInvItemActionDropDownMenuUW>(GetWorld(), DropDownMenuUWClass);

	if (DropDownMenuUW)
	{
		DropDownMenuUW->AddToViewport();

		FWidgetTransform DropDownMenuTransform;
		DropDownMenuTransform.Translation = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
		DropDownMenuUW->Initialize(DropDownMenuTransform);
	}
}
