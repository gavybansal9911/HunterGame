// Hunter Game by Gamer Guru.


#include "AI/AIControllerBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionSystem.h"

AAIControllerBase::AAIControllerBase()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
	BehaviorTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("Behavior Tree"));
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));
	SenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AI Sight Config"));
	SenseConfig_Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("AI Hearing Config"));
	SenseConfig_Damage = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("AI Damage Config"));
	PerceptionComponent->ConfigureSense(*SenseConfig_Sight);
	PerceptionComponent->ConfigureSense(*SenseConfig_Hearing);
	PerceptionComponent->ConfigureSense(*SenseConfig_Damage);
	PerceptionComponent->SetDominantSense(SenseConfig_Damage->GetSenseImplementation());
}

void AAIControllerBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AAIControllerBase::OnPerceptionUpdated);
}

void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAIControllerBase::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	CanSenseActorData SenseActorData;
	
	for (AActor* Actor : UpdatedActors)
	{
		// Sensed Sight?
		SenseActorData = CanSenseActor(Actor, EAISense::EAIS_Sight);
		if (SenseActorData.Sensed)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, FString("Sight Triggered"));
		}

		// Sensed Hearing?
		SenseActorData = CanSenseActor(Actor, EAISense::EAIS_Hearing);
		if (SenseActorData.Sensed)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, FString("Hearing Triggered"));
		}

		// Sensed Damage?
		SenseActorData = CanSenseActor(Actor, EAISense::EAIS_Damage);
		if (SenseActorData.Sensed)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, FString("Damage Triggered"));
		}
	}
}

CanSenseActorData AAIControllerBase::CanSenseActor(AActor* Actor, EAISense Sense)
{
	FActorPerceptionBlueprintInfo ActorPerceptionBlueprintInfo;
	PerceptionComponent->GetActorsPerception(Actor,ActorPerceptionBlueprintInfo);
	
	for (FAIStimulus AIStimulas : ActorPerceptionBlueprintInfo.LastSensedStimuli)
	{
		TSubclassOf<UAISense> SenseClass = UAIPerceptionSystem::GetSenseClassForStimulus(this, AIStimulas);

		CanSenseActorData Local_CanSenseActorData;
		Local_CanSenseActorData.Stimulus = AIStimulas;
		switch (Sense)
		{
			case EAISense::EAIS_Sight:
				if (SenseClass == SenseConfig_Sight->GetClass())
				{
					Local_CanSenseActorData.Sensed = AIStimulas.WasSuccessfullySensed();
					return Local_CanSenseActorData;
				}
				break;
			case EAISense::EAIS_Hearing:
				if (SenseClass == SenseConfig_Hearing->GetClass())
				{
					Local_CanSenseActorData.Sensed = AIStimulas.WasSuccessfullySensed();
					return Local_CanSenseActorData;
				}
				break;
			case EAISense::EAIS_Damage:
				if (SenseClass == SenseConfig_Damage->GetClass())
				{
					Local_CanSenseActorData.Sensed = AIStimulas.WasSuccessfullySensed();
					return Local_CanSenseActorData;
				}
				break;
			default:
				break;
		}
	}
	CanSenseActorData CanSenseActorData;
	return CanSenseActorData;
}

void AAIControllerBase::HandleSightSense(AActor* SensedActor)
{
}

void AAIControllerBase::HandleHearingSense(FVector SoundOrigin_Loc)
{
}

void AAIControllerBase::HandleDamageSense()
{
}
