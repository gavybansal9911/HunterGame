// Hunter Game by Gamer Guru.


#include "Character/Animal/AnimalAIControllerBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AI/AI_Types.h"
#include "Character/Animal/BaseAnimal.h"

AAnimalAIControllerBase::AAnimalAIControllerBase()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));
	
	FAISenseAffiliationFilter AISenseAffiliationFilter;
	AISenseAffiliationFilter.bDetectEnemies = true;
	AISenseAffiliationFilter.bDetectFriendlies = true;
	AISenseAffiliationFilter.bDetectNeutrals = true;
	
	SenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AI Sight Config"));
	PerceptionComponent->ConfigureSense(*SenseConfig_Sight);
	SenseConfig_Sight->SightRadius = 2500.f;
	SenseConfig_Sight->LoseSightRadius = 4000.f;
	SenseConfig_Sight->PeripheralVisionAngleDegrees = 65.f;
	SenseConfig_Sight->DetectionByAffiliation = AISenseAffiliationFilter;
	SenseConfig_Sight->SetMaxAge(5.f);

	SenseConfig_Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("AI Hearing Config"));
	PerceptionComponent->ConfigureSense(*SenseConfig_Hearing);
	SenseConfig_Hearing->DetectionByAffiliation = AISenseAffiliationFilter;
	SenseConfig_Hearing->HearingRange = 1500.f;
	SenseConfig_Hearing->SetMaxAge(3.f);

	SenseConfig_Damage = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("AI Damage Config"));
	PerceptionComponent->ConfigureSense(*SenseConfig_Damage);
	SenseConfig_Damage->SetMaxAge(3.f);

	PerceptionComponent->SetDominantSense(SenseConfig_Damage->GetSenseImplementation());  // Dominant Sense
}

void AAnimalAIControllerBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Init_Controller();
	
	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AAnimalAIControllerBase::OnPerceptionUpdated);
}

void AAnimalAIControllerBase::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	CanSenseActorData_Animal SenseActorData_Animal;

	for (AActor* Actor : UpdatedActors)
	{
		SenseActorData_Animal = CheckCanSenseActor(Actor, EAIPerceptionSense::EAIS_Sight);
		if (SenseActorData_Animal.Sensed)
		{
			HandleSightSense(Actor);
		}

		SenseActorData_Animal = CheckCanSenseActor(Actor, EAIPerceptionSense::EAIS_Damage);
		if (SenseActorData_Animal.Sensed)
		{
			HandleDamageSense(Actor);
		}

		SenseActorData_Animal = CheckCanSenseActor(Actor, EAIPerceptionSense::EAIS_Hearing);
		if (SenseActorData_Animal.Sensed)
		{
			HandleHearingSense(SenseActorData_Animal.Stimulus.StimulusLocation);
		}
	}
}

CanSenseActorData_Animal AAnimalAIControllerBase::CheckCanSenseActor(AActor* Actor, EAIPerceptionSense Sense)
{
	FActorPerceptionBlueprintInfo ActorPerceptionBlueprintInfo;
	PerceptionComponent->GetActorsPerception(Actor,ActorPerceptionBlueprintInfo);

	TSubclassOf<UAISense> SightSenseClass = UAISense_Sight::StaticClass();
	TSubclassOf<UAISense> HearingSenseClass = UAISense_Hearing::StaticClass();
	TSubclassOf<UAISense> DamageSenseClass = UAISense_Damage::StaticClass();

	for (FAIStimulus AIStimulas : ActorPerceptionBlueprintInfo.LastSensedStimuli)
	{
		TSubclassOf<UAISense> SenseClass = UAIPerceptionSystem::GetSenseClassForStimulus(this, AIStimulas);

		CanSenseActorData_Animal Local_CanSenseActorData_Animal;
		Local_CanSenseActorData_Animal.Stimulus = AIStimulas;
		if (Sense == EAIPerceptionSense::EAIS_Sight)
		{
			if (SenseClass == SightSenseClass)
			{
				Local_CanSenseActorData_Animal.Sensed = AIStimulas.WasSuccessfullySensed();
				return Local_CanSenseActorData_Animal;
			}
		}
		else if (Sense == EAIPerceptionSense::EAIS_Hearing)
		{
			if (SenseClass == HearingSenseClass)
			{
				Local_CanSenseActorData_Animal.Sensed = AIStimulas.WasSuccessfullySensed();
				return Local_CanSenseActorData_Animal;
			}
		}
		else if (Sense == EAIPerceptionSense::EAIS_Damage)
		{
			if (SenseClass == DamageSenseClass)
			{
				Local_CanSenseActorData_Animal.Sensed = AIStimulas.WasSuccessfullySensed();
				return Local_CanSenseActorData_Animal;
			}
		}
	}
	CanSenseActorData_Animal CanSenseActorData_Animal;
	return CanSenseActorData_Animal;
}

void AAnimalAIControllerBase::Init_Controller()
{
	OwnerAnimalCharacter = Cast<ABaseAnimal>(GetPawn());
	if (OwnerAnimalCharacter)
	{
		OnOwnerAnimalCharacterSet();
	}
}

void AAnimalAIControllerBase::OnOwnerAnimalCharacterSet()
{
}

void AAnimalAIControllerBase::HandleSightSense(AActor* Actor)
{
	/*
	if (OwnerAnimalCharacter)
	{
		if (OwnerAnimalCharacter->IsLookingForFood())
		{
			
		}
	}*/
}

void AAnimalAIControllerBase::HandleHearingSense(FVector SoundOrigin_Loc)
{
}

void AAnimalAIControllerBase::HandleDamageSense(AActor* Actor)
{
}

FVector AAnimalAIControllerBase::GetPointOfInterest() const
{
	if (Blackboard)
	{
		return Blackboard->GetValueAsVector(FName("PointOfInterest"));
	}
	return FVector();
}
