// Hunter Game by Gamer Guru.


#include "Component/CombatComponent.h"
#include "Character/BaseCharacter.h"
#include "PlayerController/HunterPlayerController.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Weapon/Weapon.h"
#include "HUD/HunterHUD.h"

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
	DOREPLIFETIME(UCombatComponent, PrimaryWeapon);
	DOREPLIFETIME(UCombatComponent, SecondaryWeapon);
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

	if (WeaponInHand && bIsCombatEnabled)
	{
		SetHUDCrosshair(DeltaTime);

		if (bIsAiming && HunterCharacter && HunterCharacter->IsLocallyControlled())
		{
			FHitResult HitResult;
			TraceUnderCrosshair(HitResult);
			HitTarget = HitResult.ImpactPoint;
		}
	}
}

void UCombatComponent::EquipWeapon(AWeapon* Weapon)
{
	if (!Weapon || !HunterCharacter) return;
	if (Weapon->GetWeaponState() != EWeaponState::EWS_Unattached) return;
	if (CheckIfWeaponWithSameClassIsEquipped(Weapon->GetWeaponClass())) return;

	if (Weapon->AreaSphere->GetGenerateOverlapEvents()) {Weapon->AreaSphere->SetGenerateOverlapEvents(false);}
	AttachToActor(HunterCharacter, Weapon, Weapon->GetInHandAttachSocketName());
	WeaponInHand = Weapon;
	switch (Weapon->GetWeaponClass())
	{
		case EWeaponClass::EWC_Primary:
			PrimaryWeapon = Weapon;
			break;
		case EWeaponClass::EWC_Secondary:
			SecondaryWeapon = Weapon;
			break;
		default:
			break;;
	}
	bIsCombatEnabled = true;
	Weapon->SetWeaponState(EWeaponState::EWS_Attached);
	Weapon->SetWeaponAttachmentStatus(EAttachmentStatus::EAS_InHand);
	/** We are not spawning the projectile on the client so for now there is no need to disable weapon collision for clients, but this may cause issues while performing hit and damage so later, we may have to disable weapon collision for clients as well.
	* Set collision response to overlap for all channels so that the projectile or the trace(if performed from the muzzle position vector) doesn't collide with the weapon it's fired from. **/
	WeaponInHand->GetWeaponMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Weapon->SetOwner(HunterCharacter);
	HunterCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	HunterCharacter->bUseControllerRotationYaw = true;
}

void UCombatComponent::AttachToActor(const ACharacter* InParent, AActor* ActorToAttach, const FName SocketName)
{
	const FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	ActorToAttach->AttachToComponent(InParent->GetMesh(), AttachmentTransformRules, SocketName);
}

bool UCombatComponent::CheckIfWeaponWithSameClassIsEquipped(EWeaponClass WeaponClass)
{
	if (WeaponClass == EWeaponClass::EWC_Primary) { if (PrimaryWeapon) { return true; } { return false; } }
	if (WeaponClass == EWeaponClass::EWC_Secondary) { if (SecondaryWeapon) { return true; } { return false; } }
	return true;
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

		if (WeaponInHand)
		{
			CrosshairShootFactor = 1.2f;
		}
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

void UCombatComponent::TogglePrimaryWeapon()
{
	if (!PrimaryWeapon) return;

	if (WeaponInHand && WeaponInHand->GetWeaponClass() == EWeaponClass::EWC_Primary)
	{
		HunterCharacter->PlayAnimationMontage(WeaponInHand->PutWeaponInMontage, FName(), false);
		WeaponInHand = nullptr;
	}
	else
	{
		HunterCharacter->PlayAnimationMontage(PrimaryWeapon->TakeOutWeaponMontage, FName(), false);
		WeaponInHand = PrimaryWeapon;
	}
}

void UCombatComponent::ToggleSecondaryWeapon()
{
	if (!SecondaryWeapon) return;
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

void UCombatComponent::SetHUDCrosshair(float DeltaTime)
{
	if (!HunterCharacter) return;

	// Avoiding cast if HunterController is already set (cast is a heavy operation)
	HunterController = HunterController == nullptr ? Cast<AHunterPlayerController>(HunterCharacter->Controller) : HunterController;
	if (HunterController)
	{
		// Avoiding cast if HunterHUD is already set (cast is a heavy operation)
		HunterHUD = HunterHUD == nullptr ? Cast<AHunterHUD>(HunterController->GetHUD()) : HunterHUD;
		if (HunterHUD)
		{
			FHUDPackage HUDPackage;
			if (WeaponInHand && bIsAiming)
			{
				HUDPackage.CrosshairCenter = WeaponInHand->CrosshairCenter;
				HUDPackage.CrosshairLeft = WeaponInHand->CrosshairLeft;
				HUDPackage.CrosshairRight = WeaponInHand->CrosshairRight;
				HUDPackage.CrosshairTop = WeaponInHand->CrosshairTop;
				HUDPackage.CrosshairBottom = WeaponInHand->CrosshairBottom;
			}
			else
			{
				HUDPackage.CrosshairCenter = nullptr;
				HUDPackage.CrosshairLeft = nullptr;
				HUDPackage.CrosshairRight = nullptr;
				HUDPackage.CrosshairTop = nullptr;
				HUDPackage.CrosshairBottom = nullptr;
			}

			/** Calculate Crosshair Spread **/  // Calculating crosshair spread value based on different factors
			// Mapping player character velocity from [0, 600] to [0, 1]
			/* Velocity Factor */
			FVector2d WalkSpeedRange(0.f, HunterCharacter->GetCharacterMovement()->MaxWalkSpeed);
			FVector2d VelocityMultiplierRange(0.f, 1.f);
			FVector Velocity = HunterCharacter->GetVelocity();
			Velocity.Z = 0.f;
			CrosshairVelocityFactor = FMath::GetMappedRangeValueClamped(WalkSpeedRange, VelocityMultiplierRange, Velocity.Size());
			/* Velocity Factor */

			/* IsFalling Factor */
			if (HunterCharacter->GetCharacterMovement()->IsFalling())
			{
				CrosshairInAirFactor = FMath::FInterpTo(CrosshairInAirFactor, IN_AIR_CROSSHAIR_SPREAD, DeltaTime, 2.25f);
			}
			else
			{
				CrosshairInAirFactor = FMath::FInterpTo(CrosshairInAirFactor, 0, DeltaTime, 30.f);
			}
			/* IsFalling Factor */

			/* Aim Factor */
			if (bIsAiming)
			{
				CrosshairAimFactor = FMath::FInterpTo(CrosshairAimFactor, 0.30f, DeltaTime, 30.f);
			}
			else
			{
				CrosshairAimFactor = FMath::FInterpTo(CrosshairAimFactor, 0.f, DeltaTime, 30.f);
			}
			/* Aim Factor */

			/* Shoot Factor */
			CrosshairShootFactor = FMath::FInterpTo(CrosshairShootFactor, 0.F, DeltaTime, 40.f);
			/* Shoot Factor */
			
			// Set Crosshair Spread on HUDPackage
			HUDPackage.CrosshairSpread = CrosshairVelocityFactor + CrosshairInAirFactor - CrosshairAimFactor + CrosshairShootFactor;
			/** Calculate Crosshair Spread **/
			
			
			// Update HUDPackage on HunterHUD
			HunterHUD->SetHUDPackage(HUDPackage);
		}
	}
}

/** Rep Notifies **/
void UCombatComponent::OnRep_EquippedWeapon()
{
	if (HunterCharacter && WeaponInHand)
	{
		HunterCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
		HunterCharacter->bUseControllerRotationYaw = true;
		WeaponInHand->GetWeaponMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	}
}

void UCombatComponent::OnRep_PrimaryWeapon()
{
}

void UCombatComponent::OnRep_SecondaryWeapon()
{
}
/** Rep Notifies **/
