// Hunter Game by Gamer Guru.


#include "Character/Animal/BaseAnimal.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Character/Animal/AnimalAIControllerBase.h"

ABaseAnimal::ABaseAnimal()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABaseAnimal::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//AnimalAIController = Cast<AAnimalAIControllerBase>(UAIBlueprintHelperLibrary::GetAIController(this));
	AnimalAIController = Cast<AAIController>(NewController);

	if (AnimalAIController)
	{
		AnimalAIController->RunBehaviorTree(BehaviorTree);
	}
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
