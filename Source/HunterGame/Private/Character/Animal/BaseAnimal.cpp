// Hunter Game by Gamer Guru.


#include "Character/Animal/BaseAnimal.h"

ABaseAnimal::ABaseAnimal()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABaseAnimal::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseAnimal::Tick(float DeltaTime)
{
	// bCanEverTick is set to false.
	Super::Tick(DeltaTime);
}
