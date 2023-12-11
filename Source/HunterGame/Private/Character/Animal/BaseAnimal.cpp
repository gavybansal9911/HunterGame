// Hunter Game by Gamer Guru.


#include "Character/Animal/BaseAnimal.h"
#include "Character/BaseCharacter.h"
#include "Character/Animal/AnimalAIControllerBase.h"
#include "Component/AnimalInteractionComponent.h"
#include "Component/AnimalSurvivalComponent.h"
#include "Components/CapsuleComponent.h"

ABaseAnimal::ABaseAnimal()
{
	PrimaryActorTick.bCanEverTick = false;

	InteractionAreaCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Interact Area Capsule"));
	InteractionAreaCapsule->SetupAttachment(GetMesh());
	
	SurvivalComponent = CreateDefaultSubobject<UAnimalSurvivalComponent>(TEXT("Survival Component"));
	InteractionComponent = CreateDefaultSubobject<UAnimalInteractionComponent>(TEXT("Interaction Component"));
}

void ABaseAnimal::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	Init_AnimalAI(NewController);
}

void ABaseAnimal::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (InteractionAreaCapsule)
	{
		InteractionAreaCapsule->OnComponentBeginOverlap.AddDynamic(this, &ABaseAnimal::OnInteractCapsuleOverlap);
		InteractionAreaCapsule->OnComponentEndOverlap.AddDynamic(this, &ABaseAnimal::OnInteractionCapsuleEndOverlap);
	}
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

void ABaseAnimal::Init_AnimalAI(AController* NewController)
{
	AnimalAIController = Cast<AAIController>(NewController);
	if (AnimalAIController)
	{AnimalAIController->RunBehaviorTree(BehaviorTree);}
}

void ABaseAnimal::OnInteractCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(OtherActor))
	{
		BaseCharacter->SetOverlappingActor(this);
	}
}

void ABaseAnimal::OnInteractionCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(OtherActor))
	{
		BaseCharacter->SetOverlappingActor(nullptr);
	}
}

void ABaseAnimal::InteractWith(ABaseCharacter* PlayerCharacter)
{
	// TODO: Player <-> Animal interaction
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Purple, FString("Interact with animal"));
	}
}
