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

private:
	// Owner Reference
	UPROPERTY()
	TObjectPtr<ABaseAnimal> OwnerAnimalCharacter;
};
