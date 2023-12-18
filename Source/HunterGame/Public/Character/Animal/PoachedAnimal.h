// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Character/Animal/BaseAnimal.h"
#include "PoachedAnimal.generated.h"

/**
 * 
 */
UCLASS()
class HUNTERGAME_API APoachedAnimal : public ABaseAnimal
{
	GENERATED_BODY()

public:
    APoachedAnimal();
	virtual void Tick(float DeltaSeconds) override;

protected:
    virtual void BeginPlay() override;
};
