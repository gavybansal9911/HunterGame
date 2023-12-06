// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseAnimal.generated.h"

class UAnimalSurvivalComponent;
class AAnimalAIControllerBase;
class UBehaviorTree;
class AAIController;

UCLASS()
class HUNTERGAME_API ABaseAnimal : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseAnimal();
	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	/** Components **/
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UAnimalSurvivalComponent> SurvivalComponent;
	/** Components **/

private:
	// AI Controller reference
	UPROPERTY()
	AAIController* AnimalAIController;

	// AI Behaviour
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
};
