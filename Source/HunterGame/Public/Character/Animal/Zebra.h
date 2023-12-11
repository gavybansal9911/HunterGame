// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Character/Animal/BaseAnimal.h"
#include "Zebra.generated.h"

/**
 * 
 */
UCLASS()
class HUNTERGAME_API AZebra : public ABaseAnimal
{
	GENERATED_BODY()

public:
	AZebra();
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
};
