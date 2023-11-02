// Hunter Game by Gamer Guru.


#include "Component/CombatComponent.h"

#include "Character/BaseCharacter.h"
#include "Weapon/Weapon.h"

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

void UCombatComponent::ToggleCombat() const
{
	if (WeaponInHand) {WeaponInHand->AttachToActor(HunterCharacter, WeaponInHand->GetOutHandAttachSocketName());}
	if (!WeaponInHand) {WeaponInHand->AttachToActor(HunterCharacter, WeaponInHand->GetInHandAttachSocketName());}
}
