// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FinanceComponent.generated.h"

class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUNTERGAME_API UFinanceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	friend ABaseCharacter;
	UFinanceComponent();

	/** Money Management **/
	bool AddMoneyAmount(float InAmount);       // Return Value => (bool) -> Adding was successful ?
	/** Money Management **/

protected:
	virtual void BeginPlay() override;

	bool CanBuyItem(int Cost);

	void SpendMoney(int Cost);

private:
	float MoneyAmount;

public:
	FORCEINLINE float GetMoneyAmount() const {return MoneyAmount;}
	void SetMoneyAmount(float InAmount);
};
