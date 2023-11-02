// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HUNTERGAME_API IInteractInterface
{
	GENERATED_BODY()

public:
	virtual FString LookAt() = 0;
	virtual void InteractWith() = 0;
};
