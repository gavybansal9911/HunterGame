// Hunter Game by Gamer Guru.


#include "Component/AnimalSurvivalComponent.h"

UAnimalSurvivalComponent::UAnimalSurvivalComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAnimalSurvivalComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAnimalSurvivalComponent::Init_Attributes()
{
	Init_Health();
	Init_Stamina();

	OnAttributesSet();
}

void UAnimalSurvivalComponent::Init_Health()
{
	MaxHealth = 100.f;
	Health = 100.f;
}

void UAnimalSurvivalComponent::Init_Stamina()
{
	MaxStamina = 100.f;
	Stamina = 100.f;
}

void UAnimalSurvivalComponent::OnAttributesSet()
{
}

void UAnimalSurvivalComponent::ApplyDamage(float InDamageAmount)
{
	GEngine->AddOnScreenDebugMessage(-1, 34.f, FColor::Yellow, FString::Printf(TEXT("%f - %f"), Health, InDamageAmount));
	Health = FMath::Clamp(Health - InDamageAmount, 0.f, MaxHealth);
	if (Health == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 34.f, FColor::Yellow, FString("Animal is dead"));
		// Death
	}
}
