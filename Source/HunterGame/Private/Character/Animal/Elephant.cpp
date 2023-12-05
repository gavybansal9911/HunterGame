// Hunter Game by Gamer Guru.


#include "Character/Animal/Elephant.h"

AElephant::AElephant()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AElephant::BeginPlay()
{
	Super::BeginPlay();
}

void AElephant::Tick(float DeltaSeconds)
{
	// bCanEverTick is set to false.
	Super::Tick(DeltaSeconds);
}
