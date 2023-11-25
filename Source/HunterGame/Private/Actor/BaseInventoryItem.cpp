// Hunter Game by Gamer Guru.


#include "Actor/BaseInventoryItem.h"

ABaseInventoryItem::ABaseInventoryItem()
{
}

void ABaseInventoryItem::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseInventoryItem::InteractWith(ABaseCharacter* HunterCharacter)
{
	Super::InteractWith(HunterCharacter);
}

void ABaseInventoryItem::UseItem()
{
	IInventoryItemInterface::UseItem();
}

void ABaseInventoryItem::DropItem()
{
	IInventoryItemInterface::DropItem();
}
