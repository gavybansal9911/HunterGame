// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "AI_Types.h"
#include "GameFramework/Character.h"
#include "Interface/EnemyInterface.h"
#include "EnemyBase.generated.h"

class AWeapon;
class USphereComponent;
class UBehaviorTree;
class AAIControllerBase;
class UAnimMontage;

UCLASS()
class HUNTERGAME_API AEnemyBase : public ACharacter, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AEnemyBase();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;  // Called when the this character is possessed

	/** Interface **/
	UFUNCTION(BlueprintCallable)
	virtual EAIState GetEnemyState() const override;
	/** Interface **/
	
protected:
	virtual void BeginPlay() override;
	virtual void Init_Weapon();
	
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY()
	TObjectPtr<AAIControllerBase> AIController;

	// Weapon
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY()
	AWeapon* Weapon;
	
	/** Enemy States **/
	EAIState AIState = EAIState::EAIS_Passive;
	EAIMovementMode AIMovementMode = EAIMovementMode::EMM_Idle;
	/** Enemy States **/

	/** Animation **/
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* DaggerAttackMontage = nullptr;
	/** Animation **/

public:
	FORCEINLINE AWeapon* GetOwnedWeapon() const {return Weapon;}
};
