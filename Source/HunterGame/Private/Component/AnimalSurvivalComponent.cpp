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
