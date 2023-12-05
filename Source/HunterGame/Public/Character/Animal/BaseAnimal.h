// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseAnimal.generated.h"

class AAnimalAIControllerBase;
class UBehaviorTree;
class AAIController;

UCLASS()
class HUNTERGAME_API ABaseAnimal : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseAnimal();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	// AI Controller reference
	UPROPERTY()
	AAnimalAIControllerBase* AnimalAIController;

	// AI Behaviour
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
};
