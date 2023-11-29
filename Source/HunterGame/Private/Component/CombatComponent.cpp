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
#include "TimerManager.h"

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
	DOREPLIFETIME(UCombatComponent, CombatState);

	/** Temporary **/
	DOREPLIFETIME_CONDITION(UCombatComponent, CarriedAmmo, COND_OwnerOnly);
	/** Temporary **/
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

		if (HunterCharacter && bIsAiming && HunterCharacter->IsLocallyControlled())
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
	if (WeaponInHand) return;
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
			break;
	}
	bIsCombatEnabled = true;
	Weapon->SetWeaponState(EWeaponState::EWS_Attached);
	Weapon->SetWeaponAttachmentStatus(EAttachmentStatus::EAS_InHand);
	/** We are not spawning the projectile on the client so for now there is no need to disable weapon collision for clients, but this may cause issues while performing hit and damage so later, we may have to disable weapon collision for clients as well.
	* Set collision response to overlap for all channels so that the projectile or the trace(if performed from the muzzle position vector) doesn't collide with the weapon it's fired from. **/
	WeaponInHand->GetWeaponMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	WeaponInHand->SetOwner(HunterCharacter);
	WeaponInHand->SetHUDWeaponAmmo();
	HunterCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	HunterCharacter->bUseControllerRotationYaw = true;
	if (HunterHUD)
	{
		HunterHUD->OnCombatEnabled();
	}
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

void UCombatComponent::Reload()
{
	if (CarriedAmmo > 0 && CombatState == ECombatState::ECS_Unoccupied)
	{
		ServerReload();
	}
}

void UCombatComponent::ServerReload_Implementation()
{
	if (HunterCharacter == nullptr || WeaponInHand == nullptr) return;
	
	int32 ReloadAmount = CalcAmountToReload();
	CarriedAmmo = HunterCharacter->GetAmmoInInventory() - ReloadAmount;
	WeaponInHand->AddAmmoToWeapon(ReloadAmount);
	HunterCharacter->RemoveAmmoFromInventory(ReloadAmount);
	
	CombatState = ECombatState::ECS_Reloading;
	PlayReloadMontage();    // This function further calls a generic PlayAnimationMontage which is set in a way that the montage is played for the server and all the clients so, no need to replicate this montage here again.
}

void UCombatComponent::HandleReload()
{
}

void UCombatComponent::PlayReloadMontage()
{
	if (WeaponInHand == nullptr || HunterCharacter == nullptr) return;

	FName SectionName;
	switch (bIsAiming)
	{
	case true:
		SectionName = FName("Reload_Ironsights");
		break;
	case false:
		SectionName = FName("Reload_Hip");
	}
	HunterCharacter->PlayAnimationMontage(WeaponInHand->ReloadMontage, SectionName, true);
}

void UCombatComponent::OnReloadEnd()
{
	if (HunterCharacter == nullptr) return;

	if (HunterCharacter->HasAuthority())
	{
		CombatState = ECombatState::ECS_Unoccupied;	
	}
}

int32 UCombatComponent::CalcAmountToReload()
{
	if (HunterCharacter == nullptr) return 0;
	if (WeaponInHand == nullptr) return 0;
	
	int32 RoomInMag = WeaponInHand->GetMagazineSize() - WeaponInHand->GetAmmoInWeapon();
	int32 AmountCarried = HunterCharacter->GetAmmoInInventory();
	int32 Least = FMath::Min(RoomInMag, AmountCarried);

	return FMath::Clamp(RoomInMag, 0, Least);
}

void UCombatComponent::TogglePrimaryWeaponAttachment()
{
	if (HunterCharacter->HasAuthority())
	{
		if (WeaponInHand && WeaponInHand->GetWeaponClass() == EWeaponClass::EWC_Primary)
		{
			AttachToActor(HunterCharacter, WeaponInHand, WeaponInHand->GetOutHandAttachSocketName());
			WeaponInHand->SetWeaponAttachmentStatus(EAttachmentStatus::EAS_OutHand);
			WeaponInHand = nullptr;
			DisableCombat();
		}
		else if (WeaponInHand == nullptr && PrimaryWeapon)
		{
			AttachToActor(HunterCharacter, PrimaryWeapon, PrimaryWeapon->GetInHandAttachSocketName());
			PrimaryWeapon->SetWeaponAttachmentStatus(EAttachmentStatus::EAS_InHand);
			WeaponInHand = PrimaryWeapon;
			EnableCombat();
		}
	}
	else if (!HunterCharacter->HasAuthority() && HunterCharacter->IsLocallyControlled())
	{
		
		if (WeaponInHand && WeaponInHand->GetWeaponClass() == EWeaponClass::EWC_Primary)
		{
			AttachToActor(HunterCharacter, WeaponInHand, WeaponInHand->GetOutHandAttachSocketName());
			WeaponInHand->SetWeaponAttachmentStatus(EAttachmentStatus::EAS_OutHand);
			WeaponInHand = nullptr;
			DisableCombat();
		}
		else if (WeaponInHand == nullptr && PrimaryWeapon)
		{
			AttachToActor(HunterCharacter, PrimaryWeapon, PrimaryWeapon->GetInHandAttachSocketName());
			PrimaryWeapon->SetWeaponAttachmentStatus(EAttachmentStatus::EAS_InHand);
			WeaponInHand = PrimaryWeapon;
			EnableCombat();
		}
	}
}

void UCombatComponent::ToggleSecondaryWeaponAttachment()
{
	if (HunterCharacter->HasAuthority())
	{
		if (WeaponInHand && WeaponInHand->GetWeaponClass() == EWeaponClass::EWC_Secondary)
		{
			AttachToActor(HunterCharacter, WeaponInHand, WeaponInHand->GetOutHandAttachSocketName());
			WeaponInHand->SetWeaponAttachmentStatus(EAttachmentStatus::EAS_OutHand);
			WeaponInHand = nullptr;
			DisableCombat();
		}
		else if (WeaponInHand == nullptr && SecondaryWeapon)
		{
			AttachToActor(HunterCharacter, SecondaryWeapon, SecondaryWeapon->GetInHandAttachSocketName());
			SecondaryWeapon->SetWeaponAttachmentStatus(EAttachmentStatus::EAS_InHand);
			WeaponInHand = SecondaryWeapon;
			EnableCombat();
		}
	}
	else if (!HunterCharacter->HasAuthority() && HunterCharacter->IsLocallyControlled())
	{
		if (WeaponInHand && WeaponInHand->GetWeaponClass() == EWeaponClass::EWC_Secondary)
		{
			AttachToActor(HunterCharacter, WeaponInHand, WeaponInHand->GetOutHandAttachSocketName());
			WeaponInHand->SetWeaponAttachmentStatus(EAttachmentStatus::EAS_OutHand);
			WeaponInHand = nullptr;
			DisableCombat();
		}
		else if (WeaponInHand == nullptr && SecondaryWeapon)
		{
			AttachToActor(HunterCharacter, SecondaryWeapon, SecondaryWeapon->GetInHandAttachSocketName());
			SecondaryWeapon->SetWeaponAttachmentStatus(EAttachmentStatus::EAS_InHand);
			WeaponInHand = SecondaryWeapon;
			EnableCombat();
		}
	}
}

void UCombatComponent::DisableCombat()
{
	SetIsCombatEnabled(false);
	HunterCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
	HunterCharacter->bUseControllerRotationYaw = false;
	if (HunterHUD)
	{
		HunterHUD->OnCombatDisabled();
	}
}

void UCombatComponent::EnableCombat()
{
	if (HunterCharacter == nullptr) return;
	
	SetIsCombatEnabled(true);
	HunterCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	HunterCharacter->bUseControllerRotationYaw = true;
	CarriedAmmo = HunterCharacter->GetAmmoInInventory();
	if (HunterHUD)
	{
		HunterHUD->OnCombatEnabled();
	}
	if (WeaponInHand && WeaponInHand->GetOwner())
	{
		WeaponInHand->SetHUDWeaponAmmo();
	}
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
		//FHitResult HitResult;
		//TraceUnderCrosshair(HitResult);	
		Shoot();
	}
}

bool UCombatComponent::CanShoot()
{
	if (WeaponInHand == nullptr) return false;
	return bCanShoot && CombatState == ECombatState::ECS_Unoccupied;
}

void UCombatComponent::OnShootFailedDueToEmptyMagazine()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Purple, FString("Shoot failed due to 0 ammo in weapon, TODO: Play a weapon animation for no bullet shooting try"));
	}
}

void UCombatComponent::Shoot()
{
	if (!CanShoot()) return;
	if (WeaponInHand)
	{
		if (WeaponInHand->IsMagazineEmpty())
		{
			OnShootFailedDueToEmptyMagazine();
			return;
		}
	}

	bCanShoot = false;
	ServerShoot(bShootButtonPressed, HitTarget);
	if (WeaponInHand)
	{
		CrosshairShootFactor = 1.2f;
	}
	StartFireTimer();
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
	//if (HunterCharacter && bShootButtonPressed)
	if (HunterCharacter && bShootButtonPressed && CombatState == ECombatState::ECS_Unoccupied)
	{
		HunterCharacter->PlayShootMontage(bIsAiming);
		WeaponInHand->Shoot(TraceHitTarget);                        // Shoot
	}
}

void UCombatComponent::OnTogglePrimaryWeaponButtonPressed()
{
	if (!PrimaryWeapon) return;

	if (WeaponInHand && WeaponInHand->GetWeaponClass() == EWeaponClass::EWC_Primary)
	{
		HunterCharacter->PlayAnimationMontage(WeaponInHand->PutWeaponInMontage, FName(), false);
	}
	else if (WeaponInHand == nullptr)
	{
		HunterCharacter->PlayAnimationMontage(PrimaryWeapon->TakeOutWeaponMontage, FName(), false);
	}
}

void UCombatComponent::OnToggleSecondaryWeaponButtonPressed()
{
	if (!SecondaryWeapon) return;

	if (WeaponInHand && WeaponInHand->GetWeaponClass() == EWeaponClass::EWC_Secondary)
	{
		HunterCharacter->PlayAnimationMontage(WeaponInHand->PutWeaponInMontage, FName(), false);
	}
	else if (WeaponInHand == nullptr)
	{
		HunterCharacter->PlayAnimationMontage(SecondaryWeapon->TakeOutWeaponMontage, FName(), false);
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

void UCombatComponent::StartFireTimer()
{
	if (WeaponInHand == nullptr || HunterCharacter == nullptr) return;
	
	HunterCharacter->GetWorldTimerManager().SetTimer(FireTimer, this, &UCombatComponent::FireTimerFinished, WeaponInHand->GetAutoFireDelay());
}

void UCombatComponent::FireTimerFinished()
{
	bCanShoot = true;
	if (bShootButtonPressed && WeaponInHand && WeaponInHand->IsWeaponAutomatic())
	{
		Shoot();
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

void UCombatComponent::OnRep_CombatState()
{
	switch (CombatState)
	{
		case ECombatState::ECS_Reloading:
			HandleReload();
			break;
		default:
			break;
	}
}

void UCombatComponent::OnRep_CarriedAmmo()
{
}
/** Rep Notifies **/

/** Event Trigger CallBacks **/
void UCombatComponent::OnInventoryUpdated()
{
	if (HunterCharacter == nullptr || WeaponInHand == nullptr) return;
	CarriedAmmo = HunterCharacter->GetAmmoInInventory();
	HunterController->SetHUDWeaponAmmo(WeaponInHand->GetAmmoInWeapon(), CarriedAmmo);
}
/** Event Trigger CallBacks **/
