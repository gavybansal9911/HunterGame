// Hunter Game by Gamer Guru.


#include "Component/InteractionComponent.h"
#include "Weapon/Weapon.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInteractionComponent::Interact()
{
	if (OverlappingActor)
	{
		if (AWeapon* Weapon = Cast<AWeapon>(OverlappingActor))
		{
			Weapon->Equip();
			OverlappingActor = nullptr;
		}
	}
}