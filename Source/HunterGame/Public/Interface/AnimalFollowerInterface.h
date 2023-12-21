// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AnimalFollowerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAnimalFollowerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HUNTERGAME_API IAnimalFollowerInterface
{
	GENERATED_BODY()

public:
	virtual AActor* GetLeaderActor();
};
