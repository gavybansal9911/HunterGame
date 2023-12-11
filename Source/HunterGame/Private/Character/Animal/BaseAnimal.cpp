// Hunter Game by Gamer Guru.


#include "Character/Animal/BaseAnimal.h"
#include "Character/Animal/AnimalAIControllerBase.h"
#include "Component/AnimalInteractionComponent.h"
#include "Component/AnimalSurvivalComponent.h"

ABaseAnimal::ABaseAnimal()
{
	PrimaryActorTick.bCanEverTick = false;

	SurvivalComponent = CreateDefaultSubobject<UAnimalSurvivalComponent>(TEXT("Survival Component"));
	InteractionComponent = CreateDefaultSubobject<UAnimalInteractionComponent>(TEXT("Interaction Component"));
}

void ABaseAnimal::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	AnimalAIController = Cast<AAIController>(NewController);

	if (AnimalAIController)
	{
		AnimalAIController->RunBehaviorTree(BehaviorTree);
	}
}

void ABaseAnimal::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (SurvivalComponent)
		{SurvivalComponent->OwnerAnimalCharacter = this;}
	if (InteractionComponent)
		{InteractionComponent->OwnerAnimalCharacter = this;}
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
