// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "AI_Types.h"
#include "Animation/AnimInstance.h"
#include "Weapon/WeaponTypes.h"
#include "AIEnemyAnimInstance.generated.h"

class AWeapon;
class AEnemyBase;
/**
 * 
 */
UCLASS()
class HUNTERGAME_API UAIEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	// Owner Reference
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	AEnemyBase* OwnerAIEnemyCharacter;
	
	/** Basic Movement **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float Speed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsInAir;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsAccelerating;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsCrouched;

	FRotator CharacterRotationLastFrame;
	FRotator CharacterRotationThisFrame;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float Lean;

	FRotator DeltaRotation; // For smooth strafing
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float YawOffset;
	/** Basic Movement **/

	/** Combat **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bHaveWeapon;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bWeaponIsInHand;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	EWeaponType EquippedWeaponType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	AWeapon* EquippedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	EWeaponName EquippedWeaponName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bIsAiming;
	/** Combat **/
};
