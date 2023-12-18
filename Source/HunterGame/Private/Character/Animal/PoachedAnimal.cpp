// Hunter Game by Gamer Guru.


#include "Character/Animal/PoachedAnimal.h"

APoachedAnimal::APoachedAnimal()
{
	PrimaryActorTick.bCanEverTick = false;

	Tags.AddUnique(FName("Poached"));
	Tags.AddUnique(FName("PoachedAnimal"));
}

void APoachedAnimal::BeginPlay()
{
	Super::BeginPlay();
}

void APoachedAnimal::Tick(float DeltaSeconds)
{
	// bCanEverTick is set to false.
	Super::Tick(DeltaSeconds);
}
