// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "AI_Types.h"
#include "Component/AIEnemy/AIEnemyCombatComponent.h"
#include "GameFramework/Character.h"
#include "Interface/EnemyInterface.h"
#include "Interface/HitInterface.h"
#include "Interface/HumanInterface.h"
#include "EnemyBase.generated.h"

class UStatsComponent;
class UAIEnemyCombatComponent;
class AWeapon;
class USphereComponent;
class UBehaviorTree;
class AAIControllerBase;
class UAnimMontage;

UCLASS()
class HUNTERGAME_API AEnemyBase : public ACharacter, public IEnemyInterface, public IHumanInterface, public IHitInterface
{
	GENERATED_BODY()

public:
	AEnemyBase();
	virtual void PossessedBy(AController* NewController) override;  // Called when the this character is possessed
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	/** Interface **/
	virtual void GetHit() override;
	
	UFUNCTION(BlueprintCallable)
	virtual EAIState GetEnemyState() const override;
	/** Interface **/

	/** Combat **/
	void ToggleWeapon();
	UFUNCTION(BlueprintCallable)
	void ToggleWeaponAnimNotifyCallBack();

	void UpdateAttackRadius();

	void Attack();
	/** Combat **/

	void OnAIStateSetAsRunningAway();
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCauser);

	void ReportDamageEvent(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UAIEnemyCombatComponent> CombatComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStatsComponent> StatsComponent;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY()
	TObjectPtr<AAIControllerBase> AIController;
	
	/** Enemy States **/
	EAIState AIState = EAIState::EAIS_Hunting;
	EAIMovementMode AIMovementMode = EAIMovementMode::EMM_Idle;
	EAIEnemyActionState AIActionState = EAIEnemyActionState::EAIAS_None;
	/** Enemy States **/

	UFUNCTION(BlueprintCallable)
	void OnAttackCompletedAnimNotifyCallBack();
	
public:
	AWeapon* GetOwnedWeapon() const;
	bool HaveWeaponInHand() const;

	FORCEINLINE FVector GetHitTarget();
	
	UFUNCTION(BlueprintCallable)
	AActor* Get_TargetActor_BB() const;
	
	FORCEINLINE EAIEnemyActionState GetEnemyActionState() const {return AIActionState;}
	FORCEINLINE bool IsAiming() const {return CombatComponent && CombatComponent->bIsAiming;}
	
	void SetEnemyActionState(EAIEnemyActionState InActionState);
};
