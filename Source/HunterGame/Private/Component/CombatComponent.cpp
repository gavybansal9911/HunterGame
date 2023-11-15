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
	SetIsReplicatedByDefault(true);
}

void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCombatComponent, WeaponInHand);
	DOREPLIFETIME(UCombatComponent, bIsCombatEnabled);
	DOREPLIFETIME(UCombatComponent, bIsAiming);
	DOREPLIFETIME(UCombatComponent, bShootButtonPressed);
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	if (HunterCharacter)
	{
		HunterCharacter->GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	}
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
	if (HunterCharacter)
	{
		HunterCharacter->GetCharacterMovement()->MaxWalkSpeed = bAiming ? AimWalkSpeed : BaseWalkSpeed;
	}
	ServerSetAiming(bIsAiming);
}

void UCombatComponent::ServerSetAiming_Implementation(bool bAiming)
{
	bIsAiming = bAiming;
	if (HunterCharacter)
	{
		HunterCharacter->GetCharacterMovement()->MaxWalkSpeed = bAiming ? AimWalkSpeed : BaseWalkSpeed;
	}
}

void UCombatComponent::ShootButtonPressed(bool bPressed)
{
	bShootButtonPressed = bPressed;
	
	if (bShootButtonPressed)
	{
		ServerShoot(bShootButtonPressed);
	}
}

void UCombatComponent::ServerShoot_Implementation(bool bShootPressed)
{
	bShootButtonPressed = bShootPressed;  // Set bShootButtonPressed from the Server
	// Calling Multicast server RPC from a server RPC so that the Multicast RPC runs on server and all clients.
	MulticastShoot(bShootButtonPressed);   // If a Multicast RPC is called from a client then it runs only on the invoking client.
}

void UCombatComponent::MulticastShoot_Implementation(bool bShootPressed)
{
	bShootButtonPressed = bShootPressed;   // Set bShootButtonPressed from all clients(MulticastShoot is called from the server)
	if (WeaponInHand == nullptr) return;;
	if (HunterCharacter && bShootButtonPressed)
	{
		HunterCharacter->PlayShootMontage(bIsAiming);
		WeaponInHand->Shoot();                        // Shoot
	}
}

/** Rep Notifies **/
void UCombatComponent::OnRep_EquippedWeapon()
{
	if (HunterCharacter && WeaponInHand)
	{
		HunterCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
		HunterCharacter->bUseControllerRotationYaw = true;
	}
}
/** Rep Notifies **/
