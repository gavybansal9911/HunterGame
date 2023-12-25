// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AI/AI_Types.h"
#include "AnimalAIControllerBase.generated.h"

class ABaseAnimal;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class UAISenseConfig_Damage;

struct CanSenseActorData_Animal
{
	bool Sensed;
	FAIStimulus Stimulus;
};

/**
 * 
 */
UCLASS()
class HUNTERGAME_API AAnimalAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	friend ABaseAnimal;
	AAnimalAIControllerBase();
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	virtual void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	CanSenseActorData_Animal CheckCanSenseActor(AActor* Actor, EAIPerceptionSense Sense);

protected:
	void HandleSightSense(AActor* Actor);
	void HandleHearingSense(FVector SoundOrigin_Loc);
	void HandleDamageSense(AActor* Actor);
	
private:
	// Behaviour
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

public:
	FVector GetPointOfInterest() const;
};
