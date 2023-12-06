// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AIEnemyAnimInstance.generated.h"

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
	/** Basic Movement **/

	/** Combat **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bIsEquipped;
	/** Combat **/
};
