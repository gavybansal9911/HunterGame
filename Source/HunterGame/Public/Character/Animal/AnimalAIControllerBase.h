// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AnimalAIControllerBase.generated.h"

class ABaseAnimal;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class UAISenseConfig_Damage;

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
};
