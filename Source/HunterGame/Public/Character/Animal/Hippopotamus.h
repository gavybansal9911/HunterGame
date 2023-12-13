// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Character/Animal/BaseAnimal.h"
#include "Hippopotamus.generated.h"

/**
 * 
 */
UCLASS()
class HUNTERGAME_API AHippopotamus : public ABaseAnimal
{
	GENERATED_BODY()

public:
	AHippopotamus();
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
};
