// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HunterAnimInstance.generated.h"

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<ABaseCharacter> HunterCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float Speed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsFalling;	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsCrouched;

	/** Leaning **/
	FRotator CharacterRotationLastFrame;
	FRotator CharacterRotationThisFrame;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float Lean;
	/** Leaning **/
};
