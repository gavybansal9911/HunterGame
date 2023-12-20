// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Character/Animal/Elephant.h"
#include "Interface/AnimalGroupLeaderInterface.h"
#include "Elephant_GroupLeader.generated.h"

class AElephant_Follower;

/**
 * 
 */
UCLASS()
class HUNTERGAME_API AElephant_GroupLeader : public AElephant, public IAnimalGroupLeaderInterface
{
	GENERATED_BODY()

public:
	AElephant_GroupLeader();
	virtual void Tick(float DeltaSeconds) override;

	// Interface
	virtual void Spawn_Group() override;
	virtual void OnGroupSpawned() override;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Group")
	int32 GroupSize = 1;

	UPROPERTY(EditAnywhere, Category = "Group")
	TSubclassOf<AElephant_Follower> ElephantFollowerCharacter_Class;

	UPROPERTY(EditAnywhere, Category = "Group")
	float GroupAreaCoverage = 3000.f;

	UPROPERTY(EditAnywhere, Category = "Group")
	float Scale3DMin = 0.45f;

	UPROPERTY(EditAnywhere, Category = "Group")
	float Scale3DMax = 1.6f;

private:
	TArray<AElephant_Follower*> GroupFollowers;
};
