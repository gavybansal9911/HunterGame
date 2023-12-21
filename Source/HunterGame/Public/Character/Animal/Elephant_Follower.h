// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Character/Animal/Elephant.h"
#include "Interface/AnimalFollowerInterface.h"
#include "Elephant_Follower.generated.h"

class AElephant_GroupLeader;

/**
 * 
 */
UCLASS()
class HUNTERGAME_API AElephant_Follower : public AElephant, public IAnimalFollowerInterface
{
	GENERATED_BODY()

public:
	AElephant_Follower();
	virtual void Tick(float DeltaSeconds) override;

	// Interface
	virtual AActor* GetLeaderActor() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	AElephant_GroupLeader* Leader;

public:
	void SetLeader(AElephant_GroupLeader* NewLeader);
};
