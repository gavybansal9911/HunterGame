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

class AEnemy_Group_Manager;
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
	virtual void GetHit(FName HitBoneName, FVector HitBoneLocation) override;
	virtual USkinnedMeshComponent* GetCharacterMesh() override;
	
	UFUNCTION(BlueprintCallable)
	virtual EAIState GetEnemyState() const override;
	/** Interface **/

	/** Combat **/
	bool ToggleWeapon();   // Return value -> Toggle weapon success ?
	UFUNCTION(BlueprintCallable)
	void ToggleWeaponAnimNotifyCallBack();

	void UpdateAttackRadius();

	void Attack();
	/** Combat **/

	void OnAIStateSetAsRunningAway();

	void OnPoacherGroupMemberStateChanged(AEnemyBase* Member);
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCauser);

	void ReportDamageEvent(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	virtual void OnDeath();
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UAIEnemyCombatComponent> CombatComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStatsComponent> StatsComponent;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY()
	TObjectPtr<AAIControllerBase> AIController;
	
	/** Enemy States **/
	//EAIState AIState = EAIState::EAIS_Hunting;
	//EAIState AIState = EAIState::EAIS_Passive;
	//EAIMovementMode AIMovementMode = EAIMovementMode::EMM_Idle;
	EAIEnemyActionState AIActionState = EAIEnemyActionState::EAIAS_None;
	/** Enemy States **/

	/** Enemy properties **/
	bool bIsLeader = false;
	/** Enemy properties **/

	UFUNCTION(BlueprintCallable)
	void OnAttackCompletedAnimNotifyCallBack();

	// Group Management
	UPROPERTY(EditAnywhere, Category = "Poacher Group")
	int32 GroupId = -1;                      // -1 if not in a group

	UPROPERTY(EditAnywhere, Category = "Poacher Group")
	AEnemy_Group_Manager* EnemyGroupManager;

	// Group Management
	virtual void Init_GroupManager();
	
public:
	AWeapon* GetOwnedWeapon() const;
	bool HaveWeaponInHand() const;

	FVector GetHitTarget() const;
	
	UFUNCTION(BlueprintCallable)
	AActor* Get_TargetActor_BB() const;
	
	FORCEINLINE EAIEnemyActionState GetEnemyActionState() const {return AIActionState;}
	FORCEINLINE bool IsAiming() const {return CombatComponent && CombatComponent->bIsAiming;}

	FORCEINLINE EAIState GetAIState() const;

	FORCEINLINE bool IsLeader() const {return bIsLeader;}

	FORCEINLINE AEnemy_Group_Manager* GetEnemyGroupManager() const {return EnemyGroupManager;};
	
	void SetEnemyActionState(EAIEnemyActionState InActionState);

	void SetGroupId(int32 InId);
	void SetGroupManager(AEnemy_Group_Manager* InManager) {EnemyGroupManager = InManager;}
};
