// Hunter Game by Gamer Guru.


#include "Component/CombatComponent.h"
#include "Character/BaseCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Weapon/Weapon.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicated(true);
}

void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCombatComponent, bIsCombatEnabled);
	DOREPLIFETIME(UCombatComponent, bIsAiming);
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCombatComponent::EquipWeapon(AWeapon* Weapon)
{
	if (!Weapon || !HunterCharacter) return;
	if (Weapon->GetWeaponState() != EWeaponState::EWS_Unattached) return;

	if (Weapon->AreaSphere->GetGenerateOverlapEvents()) {Weapon->AreaSphere->SetGenerateOverlapEvents(false);}
	AttachToActor(HunterCharacter, Weapon, Weapon->GetInHandAttachSocketName());
	Weapon->SetWeaponState(EWeaponState::EWS_Attached);
	Weapon->SetWeaponAttachmentStatus(EAttachmentStatus::EAS_InHand);
	WeaponInHand = Weapon;
	bIsCombatEnabled = true;
	HunterCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	HunterCharacter->bUseControllerRotationYaw = true;
}

void UCombatComponent::AttachToActor(const ACharacter* InParent, AActor* ActorToAttach, const FName SocketName)
{
	const FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	ActorToAttach->AttachToComponent(InParent->GetMesh(), AttachmentTransformRules, SocketName);
}

void UCombatComponent::SetAiming(bool bAiming)
{
	bIsAiming = bAiming;
	ServerSetAiming(bIsAiming);
}

void UCombatComponent::ServerSetAiming_Implementation(bool bAiming)
{
	bIsAiming = bAiming;
}
