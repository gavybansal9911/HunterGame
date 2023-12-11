// Hunter Game by Gamer Guru.


#include "Component/AnimalInteractionComponent.h"

UAnimalInteractionComponent::UAnimalInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAnimalInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}
