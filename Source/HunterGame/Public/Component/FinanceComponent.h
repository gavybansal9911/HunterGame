// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FinanceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUNTERGAME_API UFinanceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFinanceComponent();

	/** Money Management **/
	bool WithdrawAmount(float InAmount);     // Return Value => (bool) Money withdrawn successfully ?
	/** Money Management **/

protected:
	virtual void BeginPlay() override;

private:
	float MoneyAmountInPocket;
	float MoneyAmountInBank;

public:
	FORCEINLINE float GetMoneyAmountInPocket() const {return MoneyAmountInPocket;}
	FORCEINLINE float GetMoneyAmountInBank() const {return MoneyAmountInBank;}

	void SetMoneyAmountInPocket(float InAmount);
	void SetMoneyAmountInBank(float InAmount);
};
