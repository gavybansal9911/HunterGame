// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HumanInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHumanInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HUNTERGAME_API IHumanInterface
{
	GENERATED_BODY()

public:
	virtual void UpdateUIHealth();
};
