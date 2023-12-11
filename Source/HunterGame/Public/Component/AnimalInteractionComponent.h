// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AnimalInteractionComponent.generated.h"


class ABaseAnimal;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUNTERGAME_API UAnimalInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	friend ABaseAnimal;
	UAnimalInteractionComponent();

protected:
	virtual void BeginPlay() override;

private:
	// Owner reference
	TObjectPtr<ABaseAnimal> OwnerAnimalCharacter;
};
