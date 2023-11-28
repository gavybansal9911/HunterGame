// Hunter Game by Gamer Guru.


#include "Actor/BaseInventoryItem.h"

#include "Character/BaseCharacter.h"

ABaseInventoryItem::ABaseInventoryItem(): ItemData()
{
}

void ABaseInventoryItem::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseInventoryItem::InteractWith(ABaseCharacter* PlayerCharacter)
{
	if (!PlayerCharacter) return;
	Super::InteractWith(PlayerCharacter);
	
	int32 Local_Remaining = PlayerCharacter->AddItemToInventory(ItemData);
	ItemData.NumberOfElements = Local_Remaining;
	if (Local_Remaining > 0) {this->InteractWith(PlayerCharacter);}
	if (Local_Remaining == 0) {Destroy();}
}

void ABaseInventoryItem::UseItem()
{
	IInventoryItemInterface::UseItem();
}

void ABaseInventoryItem::DropItem()
{
	IInventoryItemInterface::DropItem();
}
