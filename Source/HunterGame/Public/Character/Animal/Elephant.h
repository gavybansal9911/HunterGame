// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Character/Animal/BaseAnimal.h"
#include "Elephant.generated.h"

/**
 * 
 */
UCLASS()
class HUNTERGAME_API AElephant : public ABaseAnimal
{
	GENERATED_BODY()

public:
	AElephant();
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
};
