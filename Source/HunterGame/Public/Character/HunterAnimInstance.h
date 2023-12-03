// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/CharacterTypes.h"
#include "Weapon/WeaponTypes.h"
#include "HunterAnimInstance.generated.h"

class AWeapon;
class ABaseCharacter;
/**
 * 
 */
UCLASS()
class HUNTERGAME_API UHunterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	/** Reference **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<ABaseCharacter> HunterCharacter;
	/** Reference **/

	/** Basic Movement **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float Speed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsFalling;	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsCrouched;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsAccelerating;
	/** Basic Movement **/
	
	/** Leaning **/
	FRotator CharacterRotationLastFrame;
	FRotator CharacterRotationThisFrame;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float Lean = 0.f;
	/** Leaning **/

	/** Strafing **/
	FRotator DeltaRotation; // To Smooth strafing
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float YawOffset;
	/** Strafing **/

	/** Combat **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<AWeapon> EquippedWeapon;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	EWeaponName EquippedWeaponName;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bIsCombatEnabled;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bIsAiming;
	/** Combat **/

	/** Aim Offset **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aiming")
	float AO_Yaw;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aiming")
	float AO_Pitch;
	/** Aim Offset **/

	/** Forward and Backward Inverse Reaching Kinematics ('FABRIK') **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inverse Kinematics")
	FTransform LeftHandTransform;
	/** Forward and Backward Inverse Reaching Kinematics ('FABRIK') **/

	/** Turning in Place **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	ETurningInPlace TurningInPlace;
	/** Turning in Place **/

	/** Fixing Weapon Rotation **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	FRotator RightHandRotation;
	/** Fixing Weapon Rotation **/

	/** General **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	bool bLocallyControlled;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	bool bUseFABRIK;
	/** General **/
};
