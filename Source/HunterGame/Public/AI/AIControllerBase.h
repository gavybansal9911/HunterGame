// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_Types.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIControllerBase.generated.h"

class AWeapon;
class AEnemyBase;

struct CanSenseActorData
{
	bool Sensed;
	FAIStimulus Stimulus;
};

class UBlackboardComponent;
class UBehaviorTree;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class UAISenseConfig_Damage;
/**
 * 
 */
UCLASS()
class HUNTERGAME_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	AAIControllerBase();
	virtual void PostInitializeComponents() override;

	// On Perception Updated CallBack
	UFUNCTION()
	virtual void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	CanSenseActorData CanSenseActor(AActor* Actor, EAIPerceptionSense Sense);
	
	// Handle Sense
	void HandleSightSense(AActor* SensedActor);
	void HandleHearingSense(FVector SoundOrigin_Loc);
	void HandleDamageSense(AActor* SensedActor);

	void SetStateAsPassive();
	void SetStateAsInvestigating();
	void SetStateAsHunting(AActor* TargetActor);
	void SetStateAsChasing(AActor* TargetActor);
	void SetStateAsAttacking(AActor* TargetActor);
	void SetStateAsRetreating();
	void SetStateAsRunningAway();

	// BB
	void UpdateAttackRadius(AWeapon* Weapon);

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	/** AI Perception **/
	UPROPERTY()
	UAISenseConfig_Sight* SenseConfig_Sight;

	UPROPERTY()
	UAISenseConfig_Hearing* SenseConfig_Hearing;

	UPROPERTY()
	UAISenseConfig_Damage* SenseConfig_Damage;
	/** AI Perception **/
	
private:
	UPROPERTY()
	AEnemyBase* OwnerAIEnemy;

	/** State and Properties **/
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))   // This UPROPERTY is temporary
	EAIState AIState = EAIState::EAIS_Passive;
	EAIMovementMode AIMovementMode = EAIMovementMode::EMM_Idle;
	/** State and Properties **/

	// Blackboard keys
	FName BB_TargetActor_KeyName = FName("TargetActor");
	FName BB_PointOfInterest_KeyName = FName("PointOfInterest");
	FName BB_AIState_KeyName = FName("AIState");
	FName BB_AttackRadius_KeyName = FName("AttackRadius");

public:
	AActor* GetTargetActorBB() const;
	FORCEINLINE EAIState GetEnemyAIState() const {return AIState;}
	FORCEINLINE AEnemyBase* GetAIEnemyCharacter() const {return OwnerAIEnemy;}

	void SetBBTargetActor(AActor* TargetActor);
};
