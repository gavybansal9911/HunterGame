// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AnimalSurvivalComponent.generated.h"


class ABaseAnimal;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUNTERGAME_API UAnimalSurvivalComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	friend ABaseAnimal;
	UAnimalSurvivalComponent();

protected:
	virtual void BeginPlay() override;
	virtual void Init_Attributes();
	virtual void Init_Health();
	virtual void Init_Stamina();
	virtual void OnAttributesSet();
	virtual void Init_AnimalMood();
	virtual void UpdateAnimalMood();

	virtual void DecreaseAnimalHungerFactor_Start();
	virtual void DecreaseAnimalAggressionFactor_Start();
	virtual void DecreaseAnimalFearFactor_Start();

	virtual void DecreaseAnimalHungerFactor_Update();
	virtual void DecreaseAnimalAggressionFactor_Update();
	virtual void DecreaseAnimalFearFactor_Update();

	virtual void DecreaseAnimalHungerFactor_Clear();
	virtual void DecreaseAnimalAggressionFactor_Clear();
	virtual void DecreaseAnimalFearFactor_Clear();

	// Attributes
	float Health;
	float MaxHealth;
	float Stamina;
	float MaxStamina;

private:
	// Owner Reference
	UPROPERTY()
	TObjectPtr<ABaseAnimal> OwnerAnimalCharacter;
	
	// Behavior factors  =>  All values will be in a mapped range of [0, 1];
	float HungerFactor;
	float AggressionFactor;
	float FearFactor;
	float MoodAlpha;  // Represents the intensity of current mood.
	// Behavior factors priority order: HunterFactor > AggressionFactor > FearFactor

	FTimerHandle UpdateAnimalMoodTimerHandle;
	FTimerHandle DecreaseAnimalHungerFactorTimerHandle;
	FTimerHandle DecreaseAnimalAggressionFactorTimerHandle;
	FTimerHandle DecreaseAnimalFearFactorTimerHandle;

public:
	void ApplyDamage(float InDamageAmount);
};
