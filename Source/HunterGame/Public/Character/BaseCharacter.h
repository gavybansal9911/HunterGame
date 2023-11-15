// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CharacterTypes.h"
#include "BaseCharacter.generated.h"

#define CAMERA_BOOM_IDLE_TARGET_ARM_LENGTH 375.f
#define CAMERA_BOOM_AIM_TARGET_ARM_LENGTH 250.f

class AWeapon;
class UCombatComponent;
class UInteractionComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UAnimMontage;

UCLASS()
class HUNTERGAME_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Components **/
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UInteractionComponent> InteractionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCombatComponent> Combat;
	/** Components **/

	/** Animation **/
	void PlayShootMontage(bool bAiming);
	/** Animation **/
	
protected:
	virtual void BeginPlay() override;

	/** Input CallBacks **/
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void Jump() override;
	void CrouchButtonPressed();
	void InteractButtonPressed();
	void AimButtonPressed();
	void AimButtonReleased();
	void ShootButtonPressed();
	void ShootButtonReleased();
	/** Input CallBacks **/
	
	/** Combat **/
	void AimOffset(float DeltaTime);
	void TurnInPlace(float DeltaTime);
	/** Combat **/

	/** Input CallBacks RPCs **/
	UFUNCTION(Server, Reliable)
	void ServerInteractButtonPressed();
	/** Input CallBacks RPCs **/
	
	/** Input **/
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> BaseInputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> CrouchAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> InteractAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> AimAction;	

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ShootAction;
	/** Input **/

	/** Camera **/
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> ViewCamera;
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	FVector CameraBoomIdleSocketOffset = FVector(0.f, 0.f, 0.f);     // Camera offset when not aiming
	UPROPERTY(EditAnywhere, Category = "Camera")
	FVector CameraBoomAimSocketOffset = FVector(0.f, 75.f, 75.f);    // Camera offset when aiming
	/** Camera **/

private:
	/** Character States **/
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
	EActionState ActionState = EActionState::EAS_Idle;
	ETurningInPlace TurningInPlace = ETurningInPlace::ETIP_Max;
	/** Character States **

	/** Combat **/
	float AO_Yaw;
	float InterpAO_Yaw;
	float AO_Pitch;
	FRotator StartingAimRotation;
	/** Combat **/

	/** Animation **/
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* ShootWeaponMontage;
	/** Animation **/

public:
	bool IsCombatEnabled() const;
	AWeapon* GetEquippedWeapon() const;
	bool IsAiming() const;
	FORCEINLINE float GetAO_Yaw() const {return AO_Yaw;}
	FORCEINLINE float GetAO_Pitch() const {return AO_Pitch;}
	FORCEINLINE ETurningInPlace GetTurningInPlace() const {return TurningInPlace;}
	FORCEINLINE USpringArmComponent* GetCameraBoom() const {return CameraBoom;}
	FORCEINLINE FVector GetCameraBoomIdleSocketOffset() const {return  CameraBoomIdleSocketOffset;}
	FORCEINLINE FVector GetCameraBoomAimSocketOffset() const {return  CameraBoomAimSocketOffset;}
};
