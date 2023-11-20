// Hunter Game by Gamer Guru.


#include "Character/BaseCharacter.h"
#include "CookerSettings.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "Component/CombatComponent.h"
#include "Component/InteractionComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "PlayerController/HunterPlayerController.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	NetUpdateFrequency = 66.f;  // How many times variables are replicated from server to client per sec.
	MinNetUpdateFrequency = 33.f;  // The min net update frequency to be if the variables are not changing frequently.

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
	
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction Component"));
	Combat = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat Component"));
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
	AimOffset(DeltaTime);
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseCharacter, Health);
}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (InteractionComponent) {InteractionComponent->HunterCharacter = this;}
	if(Combat) {Combat->HunterCharacter = this;}
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
	}
}

/** Interface **/
void ABaseCharacter::GetHit()
{
	if (GEngine) {GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString("Hit"));}
}
/** Interface **/

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

	const FVector2d InputValue = Value.Get<FVector2d>();
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

	if (HasAuthority())
	{
		InteractionComponent->Interact();
	}
	else
	{
		ServerInteractButtonPressed();
	}
}

void ABaseCharacter::ServerInteractButtonPressed_Implementation()
{
	if (!InteractionComponent) return;
	InteractionComponent->Interact();
}

void ABaseCharacter::AimButtonPressed()
{
	if (!Combat) return;
	Combat->SetAiming(true);
}

void ABaseCharacter::AimButtonReleased()
{
	if (!Combat) return;
	Combat->SetAiming(false);
}

void ABaseCharacter::ShootButtonPressed()
{
	if (GetCharacterMovement()->IsFalling()) return;
	if (Combat)
	{
		Combat->ShootButtonPressed(true);
	}
}

void ABaseCharacter::ShootButtonReleased()
{
	if (Combat)
	{
		Combat->ShootButtonPressed(false);
	}
}

void ABaseCharacter::ChangeCameraMode()
{
	if (CurrentCameraMode == ECameraMode::ECM_ThirdPerson)
	{
		CurrentCameraMode = ECameraMode::ECM_SemiFirstPerson;
		CameraBoom->TargetArmLength = CAMERA_BOOM_SFP_TARGET_ARM_LENGTH;
		CameraBoom->SocketOffset = CameraBoomSocketOffset_SFP;
		TP_ViewCamera->SetActive(true);
		FP_ViewCamera->SetActive(false);
	}
	else if (CurrentCameraMode == ECameraMode::ECM_SemiFirstPerson)
	{
		CurrentCameraMode = ECameraMode::ECM_FirstPerson;
		FP_ViewCamera->SetActive(true);
		TP_ViewCamera->SetActive(false);
	}
	else if (CurrentCameraMode == ECameraMode::ECM_FirstPerson)
	{
		CurrentCameraMode = ECameraMode::ECM_ThirdPerson;
		CameraBoom->TargetArmLength = CAMERA_BOOM_TP_TARGET_ARM_LENGTH;
		CameraBoom->SocketOffset = CameraBoomSocketOffset_TP;
		TP_ViewCamera->SetActive(true);
		FP_ViewCamera->SetActive(false);
	}
}

/** Stats **/
void ABaseCharacter::UpdateHUDHealth()
{
	if (HunterPlayerController)
	{
		HunterPlayerController->SetHUDHealth(Health, MaxHealth);
	}
}
/** Stats **/

/** Combat **/
void ABaseCharacter::ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatorController, AActor* DamageCauser)
{
	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);
	UpdateHUDHealth();
}

void ABaseCharacter::AimOffset(float DeltaTime)
{
	if (Combat && Combat->GetWeaponInHand() == nullptr) return;;
	
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
		if (!Combat) return;
		if (Combat->bIsAiming) {TurningInPlace = ETurningInPlace::ETIP_Right;}
	}
	else if (AO_Yaw < -45.f)
	{
		if (!Combat) return;
		if (Combat->bIsAiming) {TurningInPlace = ETurningInPlace::ETIP_Left;}
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
/** Combat **/

/** Animation **/
void ABaseCharacter::PlayShootMontage(bool bAiming)
{
	if (Combat == nullptr || Combat->GetWeaponInHand() == nullptr) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && ShootWeaponMontage)
	{
		AnimInstance->Montage_Play(ShootWeaponMontage);
		const FName SectionName = bAiming ? FName("RifleHip") : FName("RifleAim");  // Choose section name based on bAiming;
		AnimInstance->Montage_JumpToSection(SectionName, ShootWeaponMontage);
	}
}
/** Animation **/

/** Rep Notifies **/
void ABaseCharacter::OnRep_Health()
{
	UpdateHUDHealth();
}
/** Rep Notifies **/

/** Getter / Setter **/
AWeapon* ABaseCharacter::GetEquippedWeapon() const
{
	if (!Combat) return nullptr;
	return Combat->GetWeaponInHand();
}

bool ABaseCharacter::IsCombatEnabled() const
{
	return Combat && Combat->bIsCombatEnabled;
}

bool ABaseCharacter::IsAiming() const
{
	return Combat && Combat->bIsAiming;
}

FVector ABaseCharacter::GetHitTarget() const
{
	if (!Combat) return FVector();
	return Combat->HitTarget;
}
/** Getter / Setter **/
