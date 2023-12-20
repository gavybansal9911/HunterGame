// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Character/Animal/Elephant.h"
#include "Elephant_Follower.generated.h"

/**
 * 
 */
UCLASS()
class HUNTERGAME_API AElephant_Follower : public AElephant
{
	GENERATED_BODY()

public:
	AElephant_Follower();
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
};
