// Hunter Game by Gamer Guru.


#include "Actor/Finance/ValuableItem.h"
#include "Character/BaseCharacter.h"
#include "Component/FinanceComponent.h"

AValuableItem::AValuableItem()
{
	SetReplicates(true);
}

void AValuableItem::InteractWith(ABaseCharacter* PlayerCharacter)
{
	Super::InteractWith(PlayerCharacter);

	if (PlayerCharacter && PlayerCharacter->FinanceComponent)
	{
		PlayerCharacter->FinanceComponent->AddMoneyAmount(Value_InDollar);
		UE_LOG(LogTemp, Warning, TEXT("%f"), PlayerCharacter->FinanceComponent->GetMoneyAmount());
		Destroy();
	}
}
