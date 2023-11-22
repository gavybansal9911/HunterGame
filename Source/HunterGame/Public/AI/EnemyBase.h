// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "AI_Types.h"
#include "GameFramework/Character.h"
#include "Interface/EnemyInterface.h"
#include "EnemyBase.generated.h"

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
	
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY()
	TObjectPtr<AAIControllerBase> AIController;

	/** Enemy States **/
	EAIState AIState = EAIState::EAIS_None;
	EAIMovementMode AIMovementMode = EAIMovementMode::EMM_Idle;
	EEquippedWeaponType EquippedWeaponType = EEquippedWeaponType::EEWT_None;
	/** Enemy States **/

	/** Animation **/
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* DaggerAttackMontage = nullptr;
	/** Animation **/
};
