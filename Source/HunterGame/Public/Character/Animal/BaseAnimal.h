// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseAnimal.generated.h"

UCLASS()
class HUNTERGAME_API ABaseAnimal : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseAnimal();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
