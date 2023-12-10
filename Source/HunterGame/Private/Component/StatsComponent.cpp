// Hunter Game by Gamer Guru.


#include "Component/StatsComponent.h"
#include "Interface/HumanInterface.h"
#include "Net/UnrealNetwork.h"

UStatsComponent::UStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UStatsComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UStatsComponent, Health_Data, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UStatsComponent, MaxHealth_Data, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UStatsComponent, Stamina_Data, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UStatsComponent, MaxStamina_Data, COND_OwnerOnly);
}

void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UStatsComponent::Init_Attributes()
{
	Init_Attribute(Health_Data, 100.f, 100.f);
	Init_Attribute(MaxHealth_Data, 100.f, 100.f);
	Init_Attribute(Stamina_Data, 100.f, 100.f);
	Init_Attribute(MaxStamina_Data, 100.f, 100.f);
}

void UStatsComponent::Init_Attribute(FAttributeData& AttributeData, float BaseValue, float CurrentValue)
{
	AttributeData.BaseValue = BaseValue;
	AttributeData.CurrentValue = CurrentValue;
}

void UStatsComponent::AddToCurrentHealth(float Amount)
{
	float Local_NewCurrentHealth = FMath::Clamp(Health_Data.CurrentValue + Amount, 0.f, MaxHealth_Data.CurrentValue);
	Health_Data.CurrentValue = Local_NewCurrentHealth;
}

void UStatsComponent::AddToCurrentMaxHealth(float Amount)
{
	MaxHealth_Data.CurrentValue = MaxHealth_Data.CurrentValue + Amount;
}

void UStatsComponent::AddToCurrentStamina(float Amount)
{
	float Local_NewCurrentStamina = FMath::Clamp(Stamina_Data.CurrentValue + Amount, 0.f, MaxStamina_Data.CurrentValue);
	Stamina_Data.CurrentValue = Local_NewCurrentStamina;
}

void UStatsComponent::AddToCurrentMaxStamina(float Amount)
{
	MaxStamina_Data.CurrentValue = MaxStamina_Data.CurrentValue + Amount;
}

void UStatsComponent::OnRep_Health()
{
	if (OwnerHuman)
	{
		OwnerHuman->UpdateUIHealth();
	}
}

void UStatsComponent::OnRep_MaxHealth()
{
	if (OwnerHuman)
	{
		OwnerHuman->UpdateUIHealth();
	}
}

void UStatsComponent::OnRep_Stamina()
{
}

void UStatsComponent::OnRep_MaxStamina()
{
}
