// Hunter Game by Gamer Guru.


#include "Component/PhysicalAnimation_C_Component.h"
#include "PhysicsEngine/PhysicalAnimationComponent.h"

UPhysicalAnimation_C_Component::UPhysicalAnimation_C_Component()
{
	PrimaryComponentTick.bCanEverTick = false;

	BasePhysicalAnimationComponent = CreateDefaultSubobject<UPhysicalAnimationComponent>(TEXT("Physical Animation Component"));
}

void UPhysicalAnimation_C_Component::BeginPlay()
{
	Super::BeginPlay();
}

void UPhysicalAnimation_C_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// PrimaryComponentTick.bCanEverTick is set to false.
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPhysicalAnimation_C_Component::Init_Component()
{
}
