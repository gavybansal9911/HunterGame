// Hunter Game by Gamer Guru.


#include "Character/Animal/BaseAnimal.h"
#include "Character/BaseCharacter.h"
#include "Character/Animal/AnimalAIControllerBase.h"
#include "Component/AnimalInteractionComponent.h"
#include "Component/AnimalSurvivalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseAnimal::ABaseAnimal()
{
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	
	InteractionAreaCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Interact Area Capsule"));
	InteractionAreaCapsule->SetupAttachment(GetMesh());

	AnimalHead_SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Animal Head Scene Component"));
	AnimalHead_SceneComponent->SetupAttachment(GetMesh());
	
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
	{
		SurvivalComponent->OwnerAnimalCharacter = this;
		SurvivalComponent->Init_Attributes();
	}
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

float ABaseAnimal::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if (SurvivalComponent)
	{
		SurvivalComponent->ApplyDamage(DamageAmount);
		RunAwayFromPoacher(DamageCauser);
	}
	
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ABaseAnimal::Init_AnimalAI(AController* NewController)
{
	AnimalAIController = Cast<AAnimalAIControllerBase>(NewController);
	if (AAIController* AIController = Cast<AAIController>(NewController))
	{
		AIController->RunBehaviorTree(BehaviorTree);
	}
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

void ABaseAnimal::PlayAnimationMontage(UAnimMontage* Montage, FName SectionName, bool bJumpToSection)
{
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		AnimInstance->Montage_Play(Montage);

		if (bJumpToSection)
		{
			AnimInstance->Montage_JumpToSection(SectionName, Montage);
		}
	}
}

void ABaseAnimal::RunAwayFromPoacher(AActor* Poacher)
{
	// TODO: Implementation
}

void ABaseAnimal::InteractWith(ABaseCharacter* PlayerCharacter)
{
	if (GetVelocity().Size() != 0.f) return;
	if (!PlayerCharacter) return;
	
	PlayerCharacter->SetInteractionTargetActor(this);
	PlayerCharacter->OnPlayerInteractWithAnimal(Player_InteractWithAnimalMontage);
	PlayAnimationMontage(InteractWithPlayerAnimMontage, FName(), false);
}

void ABaseAnimal::GetHit()
{
	GEngine->AddOnScreenDebugMessage(-1, 34.f, FColor::Yellow, FString("Animal hit"));
	IHitInterface::GetHit();
}
