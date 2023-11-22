// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "AI/AI_Types.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HUNTERGAME_API IEnemyInterface
{
	GENERATED_BODY()

public:
	virtual EAIState GetEnemyState() const;
};
