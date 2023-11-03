// Hunter Game by Gamer Guru.


#include "Component/CombatComponent.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicated(true);
}


void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
