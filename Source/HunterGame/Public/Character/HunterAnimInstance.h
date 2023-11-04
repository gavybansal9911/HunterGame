// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
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
	/** Basic Movement **/
	
	/** Leaning **/
	FRotator CharacterRotationLastFrame;
	FRotator CharacterRotationThisFrame;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float Lean;
	/** Leaning **/

	/** Strafing **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float YawOffset;
	/** Strafing **/

	/** Combat **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<AWeapon> EquippedWeapon;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bIsCombatEnabled;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	EWeaponName EquippedWeaponName;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bIsAiming;
	/** Combat **/
};
