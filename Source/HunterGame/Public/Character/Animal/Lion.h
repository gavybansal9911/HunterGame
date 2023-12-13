// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Character/Animal/BaseAnimal.h"
#include "Lion.generated.h"

/**
 * 
 */
UCLASS()
class HUNTERGAME_API ALion : public ABaseAnimal
{
	GENERATED_BODY()

public:
    ALion();
    virtual void Tick(float DeltaSeconds) override;

protected:
    virtual void BeginPlay() override;
};
