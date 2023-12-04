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

bool UFinanceComponent::AddMoneyAmount(float InAmount)
{
	MoneyAmount = MoneyAmount + InAmount;
	return true;
}

void UFinanceComponent::SetMoneyAmount(float InAmount)
{
	MoneyAmount = InAmount;
}
