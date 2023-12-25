// Hunter Game by Gamer Guru.


#include "Character/BaseCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Actor/WeaponAmmo/WeaponAmmo.h"
#include "Camera/CameraComponent.h"
#include "Component/CombatComponent.h"
#include "Component/FinanceComponent.h"
#include "Component/InteractionComponent.h"
#include "Component/InventoryComponent.h"
#include "Component/StatsComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "PlayerController/HunterPlayerController.h"
#include "Weapon/Weapon.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	NetUpdateFrequency = 66.f;  // How many times variables are replicated from server to client per sec.
	MinNetUpdateFrequency = 33.f;  // The min net update frequency to be if the variables are not changing frequently.

	Tags.AddUnique(FName("Character"));
	Tags.AddUnique(FName("Human"));
	Tags.AddUnique(FName("BaseCharacter"));
	Tags.AddUnique(FName("PlayerTeam"));
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = CAMERA_BOOM_TP_TARGET_ARM_LENGTH;

	TP_ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person View Camera"));
	TP_ViewCamera->SetupAttachment(CameraBoom);

	FP_ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FP_ViewCamera->SetupAttachment(GetMesh()), FName("head");
	FP_ViewCamera->bUsePawnControlRotation = true;
	FP_ViewCamera->SetAutoActivate(false);
	
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 285.f, 0.f);
	
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	CharacterMovementState = ECharacterMovementState::ECMS_Running;

	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat Component"));
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction Component"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
	FinanceComponent = CreateDefaultSubobject<UFinanceComponent>(TEXT("Finance Component"));
	StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			EnhancedInputLocalPlayerSubsystem->AddMappingContext(BaseInputMappingContext, 1);
		}
	}

	HunterPlayerController = HunterPlayerController == nullptr ? Cast<AHunterPlayerController>(GetController()) : HunterPlayerController;

	UpdateHUDHealth();

	if (HasAuthority())   // Bind Receive Damage to OnTakeAnyDamage only on the server
	{
		OnTakeAnyDamage.AddDynamic(this, &ABaseCharacter::ReceiveDamage);
	}
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CombatComponent && CombatComponent->WeaponInHand)
	{
		AimOffset(DeltaTime);
	}
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ABaseCharacter, bOrientRotationToMovement_WhenInCombat);
}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (InteractionComponent) {InteractionComponent->PlayerCharacter = this;}
	if (CombatComponent) {CombatComponent->HunterCharacter = this;}
	if (InventoryComponent)
	{
		InventoryComponent->InitInventory();
		InventoryComponent->OnInventoryUpdated.AddDynamic(this, &ABaseCharacter::OnInventoryUpdated);
	}
	if (StatsComponent)
	{
		StatsComponent->OwnerHuman = this;
		StatsComponent->Init_Attributes();
	}
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,this, &ABaseCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ABaseCharacter::Jump);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ABaseCharacter::CrouchButtonPressed);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this,&ABaseCharacter::InteractButtonPressed);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &ABaseCharacter::AimButtonPressed);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &ABaseCharacter::AimButtonReleased);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &ABaseCharacter::ShootButtonPressed);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &ABaseCharacter::ShootButtonReleased);
		EnhancedInputComponent->BindAction(ChangeCameraModeAction, ETriggerEvent::Started, this, &ABaseCharacter::ChangeCameraMode);
		EnhancedInputComponent->BindAction(TogglePrimaryWeaponAction, ETriggerEvent::Started, this, &ABaseCharacter::TogglePrimaryWeaponButtonPressed);
		EnhancedInputComponent->BindAction(ToggleSecondaryWeaponAction, ETriggerEvent::Started, this, &ABaseCharacter::ToggleSecondaryWeaponButtonPressed);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &ABaseCharacter::ReloadButtonPressed);
		EnhancedInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Started, this, &ABaseCharacter::ToggleInventoryButtonPressed);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &ABaseCharacter::SprintButtonPressed);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &ABaseCharacter::SprintButtonReleased);
		EnhancedInputComponent->BindAction(WalkAction, ETriggerEvent::Started, this, &ABaseCharacter::WalkButtonPressed);
	}
}

/** Interface **/
void ABaseCharacter::GetHit(FName HitBoneName, FVector HitBoneLocation)
{
	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Cyan, HitBoneName.ToString());
	//if (GEngine) {GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString("Hit"));}
}

USkinnedMeshComponent* ABaseCharacter::GetCharacterMesh()
{
	return GetMesh();
}

void ABaseCharacter::UpdateUIHealth()
{
	UpdateHUDHealth();
}
/** Interface **/

/** Generic **/
void ABaseCharacter::PlayAnimationMontage(UAnimMontage* Montage, FName SectionName, bool bJumpToSection)
{
	if (Montage == nullptr) return;

	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		AnimInstance->Montage_Play(Montage);

		if (bJumpToSection)
		{
			AnimInstance->Montage_JumpToSection(SectionName);
		}
	}
}
/** Generic **/

/** Input CallBacks **/
void ABaseCharacter::Move(const FInputActionValue& Value)
{
	if (!Controller || GetCharacterMovement()->IsFalling()) return;

	const FVector2d InputValue = Value.Get<FVector2d>();
	const FRotator YawRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	if (InputValue.Y != 0.f)
	{
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection, InputValue.Y);
	}
	if (InputValue.X != 0.f)
	{
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection, InputValue.X);
	}
}

void ABaseCharacter::Look(const FInputActionValue& Value)
{
	if (!Controller) return;

	const FVector2d InputValue = Value.Get<FVector2d>() * HunterPlayerController->GetLookSensitivity();
	if (InputValue.X != 0.f) {AddControllerYawInput(InputValue.X);}
	if (InputValue.Y != 0.f) {AddControllerPitchInput(InputValue.Y);}
}

void ABaseCharacter::Jump()
{
	if (!Controller) return;
	ACharacter::Jump();
}

void ABaseCharacter::CrouchButtonPressed()
{
	if (!Controller || GetCharacterMovement()->IsFalling()) return;
	
	if (!bIsCrouched) {ACharacter::Crouch();}
	if (bIsCrouched) {ACharacter::UnCrouch();}
}

void ABaseCharacter::InteractButtonPressed()
{
	if (!InteractionComponent) return;
	InteractionComponent->Interact();
}

void ABaseCharacter::AimButtonPressed()
{
	if (CombatComponent == nullptr || CombatComponent->GetWeaponInHand() == nullptr) return;
	CombatComponent->SetAiming(true);
}

void ABaseCharacter::AimButtonReleased()
{
	if (!CombatComponent || CombatComponent->GetWeaponInHand() == nullptr) return;
	CombatComponent->SetAiming(false);
}

void ABaseCharacter::ShootButtonPressed()
{
	if (GetCharacterMovement()->IsFalling()) return;
	if (CombatComponent)
	{
		CombatComponent->ShootButtonPressed(true);
	}
}

void ABaseCharacter::ShootButtonReleased()
{
	if (CombatComponent)
	{
		CombatComponent->ShootButtonPressed(false);
	}
}

void ABaseCharacter::ChangeCameraMode()
{
	if (CurrentCameraMode == ECameraMode::ECM_ThirdPerson)
	{
		bOrientRotationToMovement_WhenInCombat = false;
		
		CurrentCameraMode = ECameraMode::ECM_SemiFirstPerson;
		CameraBoom->TargetArmLength = CAMERA_BOOM_SFP_TARGET_ARM_LENGTH;
		CameraBoom->SocketOffset = CameraBoomSocketOffset_SFP;
		TP_ViewCamera->SetActive(true);
		FP_ViewCamera->SetActive(false);
	}
	else if (CurrentCameraMode == ECameraMode::ECM_SemiFirstPerson)
	{
		bOrientRotationToMovement_WhenInCombat = false;
		
		CurrentCameraMode = ECameraMode::ECM_FirstPerson;
		FP_ViewCamera->SetActive(true);
		TP_ViewCamera->SetActive(false);
	}
	else if (CurrentCameraMode == ECameraMode::ECM_FirstPerson)
	{
		bOrientRotationToMovement_WhenInCombat = true;
		
		CurrentCameraMode = ECameraMode::ECM_ThirdPerson;
		CameraBoom->TargetArmLength = CAMERA_BOOM_TP_TARGET_ARM_LENGTH;
		CameraBoom->SocketOffset = CameraBoomSocketOffset_TP;
		TP_ViewCamera->SetActive(true);
		FP_ViewCamera->SetActive(false);
	}
}

void ABaseCharacter::TogglePrimaryWeaponButtonPressed()
{
	if (!CombatComponent) return;
	CombatComponent->OnTogglePrimaryWeaponButtonPressed();
}

void ABaseCharacter::ToggleSecondaryWeaponButtonPressed()
{
	if (!CombatComponent) return;
	CombatComponent->OnToggleSecondaryWeaponButtonPressed();
}

void ABaseCharacter::ReloadButtonPressed()
{
	if (!CombatComponent) return;
	CombatComponent->Reload();
}

void ABaseCharacter::ToggleInventoryButtonPressed()
{
	if (HunterPlayerController == nullptr) return;
	HunterPlayerController->ToggleInventory();
}

void ABaseCharacter::SprintButtonPressed()
{
	if (CombatComponent == nullptr || GetCharacterMovement() == nullptr) return;
	if (CombatComponent->bIsAiming) return;

	GetCharacterMovement()->MaxWalkSpeed = IsCombatEnabled() && GetEquippedWeapon() != nullptr ? InCombatSprintSpeed : SprintSpeed;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	CharacterMovementState = ECharacterMovementState::ECMS_Sprinting;
}

void ABaseCharacter::SprintButtonReleased()
{
	if (CombatComponent == nullptr || GetCharacterMovement() == nullptr) return;
	if (CombatComponent->bIsAiming) return;

	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 285.f, 0.f);
	CharacterMovementState = ECharacterMovementState::ECMS_Running;
}

void ABaseCharacter::WalkButtonPressed()
{
	if (CharacterMovementState != ECharacterMovementState::ECMS_Walking)
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 300.f, 0.f);
		CharacterMovementState = ECharacterMovementState::ECMS_Walking;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 285.f, 0.f);
		CharacterMovementState = ECharacterMovementState::ECMS_Running;
	}
}
/** Input CallBacks **/

/** Event Trigger CallBacks **/
void ABaseCharacter::OnInventoryUpdated()
{
	if (CombatComponent) {CombatComponent->OnInventoryUpdated();}
}
/** Event Trigger CallBacks **/

/** Stats **/
void ABaseCharacter::UpdateHUDHealth()
{
	if (HunterPlayerController)
	{
		HunterPlayerController->SetHUDHealth(StatsComponent->Health_Data.CurrentValue,
			StatsComponent->MaxHealth_Data.CurrentValue);
	}
}
/** Stats **/

/** Combat **/
void ABaseCharacter::ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatorController, AActor* DamageCauser)
{
	if (StatsComponent)
	{
		StatsComponent->Health_Data.CurrentValue = FMath::Clamp(
			StatsComponent->Health_Data.CurrentValue - Damage, 0.f, StatsComponent->MaxHealth_Data.CurrentValue);
		UpdateUIHealth();
		if (StatsComponent->Health_Data.CurrentValue <= 0)
		{
			//Death();
		}
	}
}

void ABaseCharacter::AimOffset(float DeltaTime)
{
	if (CombatComponent == nullptr || CombatComponent->GetWeaponInHand() == nullptr) return;
	if (bOrientRotationToMovement_WhenInCombat == true && CombatComponent->bIsAiming == false) return;
	
	FVector Velocity = GetVelocity();
	Velocity.Z = 0.f;
	const float Speed = Velocity.Size();
	const bool bIsInAir = GetCharacterMovement()->IsFalling();

	// Aim Offset Yaw
	if (Speed == 0.f && !bIsInAir)  // Standing still, not Jumping
	{
		const FRotator CurrentAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		const FRotator DeltaAimRotation = UKismetMathLibrary::NormalizedDeltaRotator(CurrentAimRotation, StartingAimRotation);
		AO_Yaw = DeltaAimRotation.Yaw;
		if (TurningInPlace == ETurningInPlace::ETIP_NotTurning)
		{
			InterpAO_Yaw = AO_Yaw;
		}
		bUseControllerRotationYaw = true;
		TurnInPlace(DeltaTime);     // Checking turn in place if standing still and not jumping
	}
	
	if (Speed > 0.f || bIsInAir)   // Running or Jumping
	{
		StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		AO_Yaw = 0.f;
		bUseControllerRotationYaw = true;
		TurningInPlace = ETurningInPlace::ETIP_NotTurning;  // Should not turn in place if running or jumping.
	}

	// Aim Offset Pitch
	AO_Pitch = GetBaseAimRotation().Pitch;
	if (AO_Pitch > 90.f && !IsLocallyControlled())
	{
		// Map Pitch from [270, 360) to [-90, 0)
		const FVector2d InRange(270.f, 360.f);
		const FVector2d OutRange(-90.f, 0.f);
		AO_Pitch = FMath::GetMappedRangeValueClamped(InRange, OutRange, AO_Pitch);
	}
}

void ABaseCharacter::TurnInPlace(float DeltaTime)
{
	// Turn in place based on the aim offset yaw value.
	if (AO_Yaw > 90.f)
	{
		TurningInPlace = ETurningInPlace::ETIP_Right;
	}
	else if (AO_Yaw < -90.f)
	{
		TurningInPlace = ETurningInPlace::ETIP_Left;
	}
	if (AO_Yaw > 45.f)
	{
		if (!CombatComponent) return;
		if (CombatComponent->bIsAiming) {TurningInPlace = ETurningInPlace::ETIP_Right;}
	}
	else if (AO_Yaw < -45.f)
	{
		if (!CombatComponent) return;
		if (CombatComponent->bIsAiming) {TurningInPlace = ETurningInPlace::ETIP_Left;}
	}
	if (TurningInPlace != ETurningInPlace::ETIP_NotTurning)
	{
		InterpAO_Yaw = FMath::FInterpTo(InterpAO_Yaw, 0.f, DeltaTime, 4.f);
		AO_Yaw = InterpAO_Yaw;
		if (FMath::Abs(AO_Yaw) < 15.f)
		{
			TurningInPlace = ETurningInPlace::ETIP_NotTurning;
			StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		}
	}
}

int32 ABaseCharacter::GetAmmoInInventory() const
{
	if (CombatComponent == nullptr || CombatComponent->bIsCombatEnabled == false) return 0;
	if (CombatComponent->GetWeaponInHand() == nullptr) return 0;
	if (InventoryComponent == nullptr) return 0;

	int32 Local_InInventoryAmmo = 0;
	
	for (FSlotData Slot : InventoryComponent->GetContent())
	{
		if (CombatComponent->GetWeaponInHand()->GetWeaponAmmoClass() == Slot.ItemData.ItemClass)
		{
			Local_InInventoryAmmo = Local_InInventoryAmmo + Slot.Quantity;
		}
	}

	return Local_InInventoryAmmo;
}

bool ABaseCharacter::RemoveAmmoFromInventory(int32 AmountOfAmmoToRemove)
{
	if (CombatComponent == nullptr || InventoryComponent == nullptr) return false;

	int Local_Index = 0;
	for (FSlotData Slot : InventoryComponent->GetContent())
	{
		if (CombatComponent->GetWeaponInHand()->GetWeaponAmmoClass() == Slot.ItemData.ItemClass)
		{
			int32 ElementsRemoved = InventoryComponent->RemoveItemFromSlot(Local_Index, AmountOfAmmoToRemove);
			if (AmountOfAmmoToRemove > ElementsRemoved)
			{
				// TODO: Resolve Issue -> Calling RemoveAmmoFromInventory creates a infinite loop (Creates a infinite loop only if inventory is full)
				//RemoveAmmoFromInventory(AmountOfAmmoToRemove - ElementsRemoved);
			}
			return true;  // Return so it doesn't remove ammo from every stack of ammo in the inventory
		}

		Local_Index++;
	}

	return false;
}

void ABaseCharacter::OnReloadEnd_AnimNotifyCallBack()
{
	if (!CombatComponent) return;;
	CombatComponent->OnReloadEnd();
}

void ABaseCharacter::TogglePrimaryWeapon_AnimNotifyCallBack()
{
	if (!CombatComponent) return;
	CombatComponent->TogglePrimaryWeaponAttachment();
}

void ABaseCharacter::ToggleSecondaryWeapon_AnimNotifyCallBack()
{
	if (!CombatComponent) return;
	CombatComponent->ToggleSecondaryWeaponAttachment();
}
/** Combat **/

void ABaseCharacter::Death()
{
	PlayAnimationMontage(DeathMontage, FName(), false);
	HunterPlayerController->OnDeath();
}

/** Interaction **/
int32 ABaseCharacter::AddItemToInventory(FItemData ItemData)
{
	if (!InventoryComponent) return -1;

	int32 Local_Remaining = InventoryComponent->AddItemToInventory(ItemData);
	return Local_Remaining;
}

void ABaseCharacter::OnPlayerInteractWithAnimal(UAnimMontage* PlayerInteractAnimMontage)
{
	if (InteractionComponent)
	{
		InteractionComponent->OnPlayerInteractWithAnimal(PlayerInteractAnimMontage);;
	}
}
/** Interaction **/

/** UI **/
void ABaseCharacter::HideCharacterOverlayUI()
{
	if (HunterPlayerController == nullptr) return;
	HunterPlayerController->HideCharacterOverlayUI();
}

void ABaseCharacter::ShowCharacterOverlayUI()
{
	if (HunterPlayerController == nullptr) return;
	HunterPlayerController->ShowCharacterOverlayUI();
}
/** UI **/


/** Animation **/
void ABaseCharacter::PlayShootMontage(bool bAiming)
{
	if (CombatComponent == nullptr || CombatComponent->GetWeaponInHand() == nullptr || GetEquippedWeapon() == nullptr) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && GetEquippedWeapon()->WeaponShootMontage)
	{
		AnimInstance->Montage_Play(GetEquippedWeapon()->WeaponShootMontage);
		FName SectionName = bAiming ? FName("Aim") : FName("Hip");  // Choose section name based on bAiming;
		AnimInstance->Montage_JumpToSection(SectionName, GetEquippedWeapon()->WeaponShootMontage);
		//PlayAnimationMontage(GetEquippedWeapon()->WeaponShootMontage, SectionName, true);
	}
}
/** Animation **/

/** Getter / Setter **/
AWeapon* ABaseCharacter::GetEquippedWeapon() const
{
	if (!CombatComponent) return nullptr;
	return CombatComponent->GetWeaponInHand();
}

bool ABaseCharacter::IsCombatEnabled() const
{
	return CombatComponent && CombatComponent->bIsCombatEnabled;
}

bool ABaseCharacter::IsAiming() const
{
	return CombatComponent && CombatComponent->bIsAiming;
}

FVector ABaseCharacter::GetHitTarget() const
{
	if (!CombatComponent) return FVector();
	return CombatComponent->HitTarget;
}

ECombatState ABaseCharacter::GetCombatState() const
{
	if (!CombatComponent) return ECombatState::ECS_Max;
	return CombatComponent->CombatState;
}

AActor* ABaseCharacter::GetInteractionTargetActor() const
{
	if (InteractionComponent)
	{
		return InteractionComponent->GetInteractionTargetActor();
	}
	return nullptr;
}

bool ABaseCharacter::CanBuyItem(FItemData ItemData) const
{
	if (!InventoryComponent || !FinanceComponent) return false;
	return FinanceComponent->CanBuyItem(ItemData.Cost) &&
		InventoryComponent->SpaceAvailable(ItemData);
}

void ABaseCharacter::SetOverlappingActor(AActor* InOverlappingActor)
{
	if (!InteractionComponent) return;
	InteractionComponent->SetOverlappingActor(InOverlappingActor);
}

void ABaseCharacter::SetInteractionTargetActor(AActor* InTargetActor)
{
	if (InteractionComponent)
	{
		InteractionComponent->SetInteractionTargetActor(InTargetActor);
	}
}
/** Getter / Setter **/
