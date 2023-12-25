// Hunter Game by Gamer Guru.


#include "Character/Animal/Hippopotamus.h"

AHippopotamus::AHippopotamus()
{
	PrimaryActorTick.bCanEverTick = false;

	Tags.Add(FName("Hippopotamus"));
}

void AHippopotamus::BeginPlay()
{
	Super::BeginPlay();
}

void AHippopotamus::Tick(float DeltaSeconds)
{
	// bCanEverTick is set to false
	Super::Tick(DeltaSeconds);
}
