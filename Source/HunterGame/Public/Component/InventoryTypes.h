#pragma once

struct FItemData
{
	FString ItemID;
	FName ItemName;
	FString Description;
	int32 NumberOfElements;
	int32 MaxStackSize;
};

struct FSlotData
{
	FString ItemID;
	int32 Quantity;
	FItemData ItemData;
};
