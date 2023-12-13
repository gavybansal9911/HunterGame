// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimalAnimInstance.generated.h"

class ABaseAnimal;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class HUNTERGAME_API UAnimalAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Owner")
	TObjectPtr<ABaseAnimal> OwnerAnimalCharacter;

	/** Basic Movement **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsAccelerating;
	/** Basic Movement **/

	/** IK **/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "IK")
	float MinDoIKRange = 20000.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IK")
	bool bShouldDoIK = false;
	/** IK **/
};
