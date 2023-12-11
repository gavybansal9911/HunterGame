// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "AnimalTypes.h"
#include "GameFramework/Character.h"
#include "Interface/InteractInterface.h"
#include "BaseAnimal.generated.h"

class UAnimalInteractionComponent;
class UAnimalSurvivalComponent;
class AAnimalAIControllerBase;
class UBehaviorTree;
class AAIController;

UCLASS()
class HUNTERGAME_API ABaseAnimal : public ACharacter, public IInteractInterface
{
	GENERATED_BODY()

public:
	ABaseAnimal();
	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;

	// Interface
	virtual void InteractWith(ABaseCharacter* PlayerCharacter) override;

protected:
	virtual void BeginPlay() override;

	virtual void Init_AnimalAI(AController* NewController);
	
	UFUNCTION()
	virtual void OnInteractCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnInteractionCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> InteractionAreaCapsule;

	/** Components **/
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UAnimalSurvivalComponent> SurvivalComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UAnimalInteractionComponent> InteractionComponent;
	/** Components **/

	// States and properties
	EAnimalName AnimalName = EAnimalName::EAN_Max;
	EAnimalModeOfFeeding AnimalModeOfFeeding = EAnimalModeOfFeeding::EAMF_Max;
	EAgeStatus AnimalAgeStatus = EAgeStatus::EAS_Max;
	EAnimalState AnimalState = EAnimalState::EAS_Max;
	EAnimalActionState AnimalActionState  = EAnimalActionState::EAAS_Max;

private:
	// AI Controller reference
	UPROPERTY()
	AAIController* AnimalAIController;

	// AI Behaviour
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

public:
	UFUNCTION(BlueprintCallable)
	inline EAgeStatus GetAnimalAgeStatus() const {return AnimalAgeStatus;}
};
