// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Actor/BaseItemActor.h"
#include "ValuableItem.generated.h"

/**
 * 
 */
UCLASS()    // This class is only for smaller Items, like coins which don't need any space in Inventory.
class HUNTERGAME_API AValuableItem : public ABaseItemActor
{
	GENERATED_BODY()

public:
	AValuableItem();
	virtual void InteractWith(ABaseCharacter* PlayerCharacter) override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Value")
	float Value_InDollar = 0.f;

public:
	float GetItemValue_InDollar() const {return Value_InDollar;}
};
