// Hunter Game by Gamer Guru.


#include "Component/FinanceComponent.h"

UFinanceComponent::UFinanceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFinanceComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UFinanceComponent::WithdrawAmount(float InAmount)
{
	if (InAmount > MoneyAmountInBank)
	{
		return false;
	}
	else
	{
		MoneyAmountInBank = MoneyAmountInBank - InAmount;
		MoneyAmountInPocket = MoneyAmountInPocket + InAmount;

		return true;
	}
}

void UFinanceComponent::SetMoneyAmountInPocket(float InAmount)
{
	MoneyAmountInPocket = InAmount;
}

void UFinanceComponent::SetMoneyAmountInBank(float InAmount)
{
	MoneyAmountInBank = InAmount;
}
