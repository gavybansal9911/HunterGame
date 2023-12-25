// Hunter Game by Gamer Guru.


#include "Character/Animal/Zebra.h"

AZebra::AZebra()
{
	PrimaryActorTick.bCanEverTick = false;

	Tags.Add(FName("Zebra"));
}

void AZebra::BeginPlay()
{
	Super::BeginPlay();
}

void AZebra::Tick(float DeltaSeconds)
{
	// bCanEverTick is set to false.
	Super::Tick(DeltaSeconds);
}
