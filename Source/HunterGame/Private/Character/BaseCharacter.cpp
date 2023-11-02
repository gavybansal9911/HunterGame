// Hunter Game by Gamer Guru.


#include "Character/BaseCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "Component/InteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 400.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("View Camera"));
	ViewCamera->SetupAttachment(CameraBoom);
	
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction Component"));
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
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InteractionComponent->HunterCharacter = this;
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,this, &ABaseCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ABaseCharacter::Jump);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ABaseCharacter::Crouch);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this,&ABaseCharacter::InteractButtonPressed);
		EnhancedInputComponent->BindAction(ToggleCombatAction, ETriggerEvent::Started, this, &ABaseCharacter::ToggleCombatButtonPressed);
	}
}

void ABaseCharacter::Move(const FInputActionValue& Value)
{
	if (!Controller) return;

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

void ABaseCharacter::Crouch()
{
	if (!Controller) return;
	
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

void ABaseCharacter::ToggleCombatButtonPressed()
{
	// TODO: Shift this functionality to a UI Option like in PUBG

	// Temporary Implementation:
}

void ABaseCharacter::ServerInteractButtonPressed_Implementation()
{
	if (!InteractionComponent) return;
	InteractionComponent->Interact();
}
