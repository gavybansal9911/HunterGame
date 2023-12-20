// Hunter Game by Gamer Guru.


#include "Character/Animal/Elephant_Follower.h"

AElephant_Follower::AElephant_Follower()
{
	PrimaryActorTick.bCanEverTick = false;

	Tags.AddUnique(FName("Follower"));
	Tags.AddUnique(FName("Elephant_Follower"));
}

void AElephant_Follower::BeginPlay()
{
	Super::BeginPlay();
}

void AElephant_Follower::Tick(float DeltaSeconds)
{
	// bCanEverTick is set to false.
	Super::Tick(DeltaSeconds);
}
