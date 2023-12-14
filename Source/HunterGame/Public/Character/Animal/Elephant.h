// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Character/Animal/BaseAnimal.h"
#include "Interface/PoachedAnimal.h"
#include "Elephant.generated.h"

/**
 * 
 */
UCLASS()
class HUNTERGAME_API AElephant : public ABaseAnimal, public IPoachedAnimal
{
	GENERATED_BODY()

public:
	AElephant();
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> ElephantTusksMesh;
};
