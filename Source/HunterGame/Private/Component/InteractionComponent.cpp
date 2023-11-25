// Hunter Game by Gamer Guru.


#include "Component/InteractionComponent.h"
#include "Weapon/Weapon.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
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
	if (OverlappingActor == nullptr) return;
	
	if (IInteractInterface* InteractiveItem = Cast<IInteractInterface>(OverlappingActor))
	{
		InteractiveItem->InteractWith(PlayerCharacter);
		OverlappingActor = nullptr;
	}
}