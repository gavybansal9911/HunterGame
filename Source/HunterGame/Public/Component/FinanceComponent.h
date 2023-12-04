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
	bool AddMoneyAmount(float InAmount);       // Return Value => (bool) -> Adding was successful ?
	/** Money Management **/

protected:
	virtual void BeginPlay() override;

private:
	float MoneyAmount;

public:
	FORCEINLINE float GetMoneyAmount() const {return MoneyAmount;}
	void SetMoneyAmount(float InAmount);
};
