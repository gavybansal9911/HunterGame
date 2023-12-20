// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AnimalGroupLeaderInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAnimalGroupLeaderInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HUNTERGAME_API IAnimalGroupLeaderInterface
{
	GENERATED_BODY()

public:
	virtual void Spawn_Group();
	virtual void OnGroupSpawned();
};
