// Hunter Game by Gamer Guru.


#include "Component/CombatComponent.h"
#include "Character/BaseCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Weapon/Weapon.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
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
	/** We are not spawning the projectile on the client so for now there is no need to disable weapon collision for clients, but this may cause issues while performing hit and damage so later, we may have to disable weapon collision for clients as well.
	* Set collision response to overlap for all channels so that the projectile or the trace(if performed from the muzzle position vector) doesn't collide with the weapon it's fired from. **/
	WeaponInHand->GetWeaponMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	bIsCombatEnabled = true;
	Weapon->SetOwner(HunterCharacter);
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
		FHitResult HitResult;
		TraceUnderCrosshair(HitResult);	
		ServerShoot(bShootButtonPressed, HitResult.ImpactPoint);
	}
}

void UCombatComponent::ServerShoot_Implementation(bool bShootPressed, const FVector_NetQuantize& TraceHitTarget)
{
	bShootButtonPressed = bShootPressed;  // Set bShootButtonPressed from the Server
	// Calling Multicast server RPC from a server RPC so that the Multicast RPC runs on server and all clients.
	MulticastShoot(bShootButtonPressed, TraceHitTarget);   // If a Multicast RPC is called from a client then it runs only on the invoking client.
}

void UCombatComponent::MulticastShoot_Implementation(bool bShootPressed, const FVector_NetQuantize& TraceHitTarget)
{
	bShootButtonPressed = bShootPressed;   // Set bShootButtonPressed from all clients(MulticastShoot is called from the server)
	if (WeaponInHand == nullptr) return;
	if (HunterCharacter && bShootButtonPressed)
	{
		HunterCharacter->PlayShootMontage(bIsAiming);
		WeaponInHand->Shoot(TraceHitTarget);                        // Shoot
	}
}

void UCombatComponent::TraceUnderCrosshair(FHitResult& TraceHitResult)
{
	FVector2d ViewportSize;
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}

	const FVector2d CrosshairLocation(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);   // Centre of viewport
	FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection;
	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(this, 0),
		CrosshairLocation, CrosshairWorldPosition, CrosshairWorldDirection);

	if (bScreenToWorld)
	{
		const FVector Start = CrosshairWorldPosition;
		const FVector End = Start + CrosshairWorldDirection * TRACE_LENGTH;    // (CrosshairWorldDirection is a unit vector)

		GetWorld()->LineTraceSingleByChannel(TraceHitResult, Start, End, ECollisionChannel::ECC_Visibility);

		if (!TraceHitResult.bBlockingHit)    // Trace doesn't hit anything
		{
			// Set TraceHitResult Impact point to because we want to spawn the projectile in the player aiming direction even if the trace doesn't hit anything
			TraceHitResult.ImpactPoint = End;
		}
		else {}                             // Trace Hit
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
