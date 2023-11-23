// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_Types.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIControllerBase.generated.h"

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
	void HandleDamageSense();

	void SetStateAsAttacking(AActor* AttackTarget);
	void SetStateAsPassive();
	
	/** State and Properties **/
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EAIState AIState = EAIState::EAIS_Passive;
	EAIMovementMode AIMovementMode = EAIMovementMode::EMM_Idle;
	EEquippedWeaponType EquippedWeaponType = EEquippedWeaponType::EEWT_None;
	/** State and Properties **/

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
};
