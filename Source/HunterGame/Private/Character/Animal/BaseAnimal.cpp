// Hunter Game by Gamer Guru.


#include "Character/Animal/BaseAnimal.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Character/Animal/AnimalAIControllerBase.h"

ABaseAnimal::ABaseAnimal()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABaseAnimal::BeginPlay()
{
	Super::BeginPlay();
	
	AnimalAIController = Cast<AAnimalAIControllerBase>(UAIBlueprintHelperLibrary::GetAIController(this));

	if (AnimalAIController)
	{
		AnimalAIController->RunBT(BehaviorTree);
	}
}

void ABaseAnimal::Tick(float DeltaTime)
{
	// bCanEverTick is set to false.
	Super::Tick(DeltaTime);
}
