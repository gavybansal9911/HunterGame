// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "AI/EnemyBase.h"
#include "EnemyGroupLeader_Base.generated.h"

/**
 * 
 */
UCLASS()
class HUNTERGAME_API AEnemyGroupLeader_Base : public AEnemyBase
{
	GENERATED_BODY()

public:
	AEnemyGroupLeader_Base();
	virtual void Tick(float DeltaSeconds) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;
};
