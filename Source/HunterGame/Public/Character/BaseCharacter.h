// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CharacterTypes.h"
#include "Component/CombatComponent.h"
#include "Component/CombatTypes.h"
#include "Component/InventoryTypes.h"
#include "Interface/HitInterface.h"
#include "BaseCharacter.generated.h"

#define CAMERA_BOOM_TP_TARGET_ARM_LENGTH 300.f
#define CAMERA_BOOM_TP_AIM_TARGET_ARM_LENGTH 125.f
#define CAMERA_BOOM_SFP_TARGET_ARM_LENGTH 0.f

class UInventoryComponent;
class AHunterPlayerController;
class AWeapon;
class UCombatComponent;
class UInteractionComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UAnimMontage;

UCLASS()
class HUNTERGAME_API ABaseCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/** Interface **/
	virtual void GetHit() override;
	/** Interface **/

	/** Generic Functions **/
	void PlayAnimationMontage(UAnimMontage* Montage, FName SectionName, bool bJumpToSection);

	UFUNCTION(Server, Reliable)
	void ServerPlayAnimationMontage(UAnimMontage* Montage, FName SectionName, bool bJumpToSection);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastPlayAnimationMontage(UAnimMontage* Montage, FName SectionName, bool bJumpToSection);
	/** Generic Functions **/
	
	/** Components **/
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UInteractionComponent> InteractionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCombatComponent> CombatComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UInventoryComponent> InventoryComponent;
	/** Components **/

	/** Animation **/
	void PlayShootMontage(bool bAiming);
	/** Animation **/

	/** Combat **/
	int32 GetAmmoInInventory() const;
	bool RemoveAmmoFromInventory(int32 AmountOfAmmoToRemove);
	/** Combat **/
	
	/** Interaction **/
	int32 AddItemToInventory(FItemData ItemData);   // Returns -1 if fails or in case of any error
	/** Interaction **/
	
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
	void ChangeCameraMode();
	void TogglePrimaryWeaponButtonPressed();
	void ToggleSecondaryWeaponButtonPressed();
	void ReloadButtonPressed();
	void ToggleInventoryButtonPressed();
	void RunButtonPressed();
	void RunButtonReleased();
	/** Input CallBacks **/

	/** Input CallBacks RPCs **/
	UFUNCTION(Server, Reliable)
	void ServerInteractButtonPressed();

	UFUNCTION(Server, Reliable)
	void ServerRunButtonPressed();
	
	UFUNCTION(Server, Reliable)
	void ServerRunButtonReleased();
	/** Input CallBacks RPCs **/

	/** Event Trigger CallBacks **/
	UFUNCTION()
	void OnInventoryUpdated();
	/** Event Trigger CallBacks **/

	/** Movement **/
	UPROPERTY(EditAnywhere, Category = "Movement")
	float WalkSpeed = 300.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RunSpeed = 600.f;
	/** Movement **/
	
	/** Combat **/
	UFUNCTION()
	void ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCauser);
	
	void AimOffset(float DeltaTime);
	void TurnInPlace(float DeltaTime);
	
	UFUNCTION(BlueprintCallable)
	void OnReloadEnd_AnimNotifyCallBack();
	
	UFUNCTION(BlueprintCallable)
	void TogglePrimaryWeapon_AnimNotifyCallBack();

	UFUNCTION(BlueprintCallable)
	void ToggleSecondaryWeapon_AnimNotifyCallBack();
	/** Combat **/

	/** Stats **/
	void UpdateHUDHealth();
	/** Stats **/
	
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

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ChangeCameraModeAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> TogglePrimaryWeaponAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ToggleSecondaryWeaponAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ReloadAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ToggleInventoryAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> RunAction;
	/** Input **/

	/** Character States **/
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
	EActionState ActionState = EActionState::EAS_Idle;
	ETurningInPlace TurningInPlace = ETurningInPlace::ETIP_Max;
	ECameraMode CurrentCameraMode = ECameraMode::ECM_ThirdPerson;
	/** Character States **
	
	/** Camera **/
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> TP_ViewCamera;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FP_ViewCamera;
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	FVector CameraBoomSocketOffset_TP = FVector(0.f, 75.f, 75.f);     // Camera offset when not aiming
	UPROPERTY(EditAnywhere, Category = "Camera")
	FVector CameraBoomAimSocketOffset_TP = FVector(0.f, 90.f, 75.f);    // Camera offset when aiming
	UPROPERTY(EditAnywhere, Category = "Camera")
	FVector CameraBoomSocketOffset_SFP = FVector(0.f, -5.f, 65.f);    // Camera offset when aiming
	/** Camera **/

	/** Animation **/
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* ShootWeaponMontage;
	
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* HitReactMontage;
	/** Animation **/
	
private:
	/** Player Controller **/
	UPROPERTY()
	AHunterPlayerController* HunterPlayerController;
	/** Player Controller **/

	/** Character Movement **/
	UPROPERTY(Replicated, EditAnywhere, Category = "Character Movement (Custom)")
	bool bOrientRotationToMovement_WhenInCombat = true;
	/** Character Movement **/
	
	/** Stats **/
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxHealth = 100.f;
	
	UPROPERTY(ReplicatedUsing = OnRep_Health, VisibleAnywhere, Category = "Player Stats")
	float Health = 100.f;
	/** Stats **/

	/** Rep Notifies **/
	UFUNCTION()
	void OnRep_Health();
	/** Rep Notifies **/
	
	/** Combat **/
	float AO_Yaw;
	float InterpAO_Yaw;
	float AO_Pitch;
	FRotator StartingAimRotation;
	/** Combat **/

public:
	bool IsCombatEnabled() const;
	AWeapon* GetEquippedWeapon() const;
	bool IsAiming() const;
	FORCEINLINE float GetAO_Yaw() const {return AO_Yaw;}
	FORCEINLINE float GetAO_Pitch() const {return AO_Pitch;}
	FORCEINLINE ETurningInPlace GetTurningInPlace() const {return TurningInPlace;}
	FORCEINLINE USpringArmComponent* GetCameraBoom() const {return CameraBoom;}
	FORCEINLINE FVector GetCameraBoomSocketOffset() const {return  CameraBoomSocketOffset_TP;}
	FORCEINLINE FVector GetCameraBoomAimSocketOffset() const {return  CameraBoomAimSocketOffset_TP;}
	FORCEINLINE ECameraMode GetCurrentCameraMode() const {return CurrentCameraMode;}
	FVector GetHitTarget() const;
	ECombatState GetCombatState() const;
	FORCEINLINE bool ShouldOrientRotationToMovement_WhenInCombat() const {return bOrientRotationToMovement_WhenInCombat;}

	void SetOverlappingActor(AActor* InOverlappingActor);
};
