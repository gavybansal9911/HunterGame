// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "AnimalTypes.h"
#include "GameFramework/Character.h"
#include "BaseAnimal.generated.h"

class UAnimalInteractionComponent;
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

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UAnimalInteractionComponent> InteractionComponent;
	/** Components **/

	// States and properties
	EAnimalName AnimalName = EAnimalName::EAN_Max;
	EAnimalModeOfFeeding AnimalModeOfFeeding = EAnimalModeOfFeeding::EAMF_Max;
	EAgeStatus AnimalAgeAgeStatus = EAgeStatus::EAS_Max;
	EAnimalState AnimalState = EAnimalState::EAS_Max;
	EAnimalActionState AnimalActionState  = EAnimalActionState::EAAS_Max;

private:
	// AI Controller reference
	UPROPERTY()
	AAIController* AnimalAIController;

	// AI Behaviour
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
};
