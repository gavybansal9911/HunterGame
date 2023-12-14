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
	float AggressionFactor;
	float FearFactor;
	float HungerFactor;
	float FriendlyFactor;

public:
	void ApplyDamage(float InDamageAmount);
};
