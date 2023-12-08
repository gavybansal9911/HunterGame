// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "AI_Types.h"
#include "GameFramework/Character.h"
#include "Interface/EnemyInterface.h"
#include "EnemyBase.generated.h"

class UAIEnemyCombatComponent;
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

	/** Combat **/
	UFUNCTION(BlueprintCallable)    // TODO: remove this temporary UFUNCTION
	void ToggleWeapon();
	UFUNCTION(BlueprintCallable)
	void ToggleWeaponAnimNotifyCallBack();
	/** Combat **/
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UAIEnemyCombatComponent> CombatComponent;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY()
	TObjectPtr<AAIControllerBase> AIController;
	
	/** Enemy States **/
	EAIState AIState = EAIState::EAIS_Passive;
	EAIMovementMode AIMovementMode = EAIMovementMode::EMM_Idle;
	/** Enemy States **/

public:
	AWeapon* GetOwnedWeapon() const;
	bool HaveWeaponInHand() const;
};
