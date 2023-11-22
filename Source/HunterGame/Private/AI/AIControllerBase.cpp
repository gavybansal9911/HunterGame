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
	BehaviorTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("Behavior Tree"));
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

void AAIControllerBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AAIControllerBase::OnPerceptionUpdated);
}

void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();
	EquippedWeaponType = EEquippedWeaponType::EEWT_Melee;
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
			HandleSightSense(Actor);
		}

		// Sensed Hearing?
		SenseActorData = CanSenseActor(Actor, EAISense::EAIS_Hearing);
		if (SenseActorData.Sensed)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, FString("Hearing Triggered"));
			HandleHearingSense(SenseActorData.Stimulus.StimulusLocation);
		}

		// Sensed Damage?
		SenseActorData = CanSenseActor(Actor, EAISense::EAIS_Damage);
		if (SenseActorData.Sensed)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, FString("Damage Triggered"));
			HandleDamageSense();
		}
	}
}

CanSenseActorData AAIControllerBase::CanSenseActor(AActor* Actor, EAISense Sense)
{
	FActorPerceptionBlueprintInfo ActorPerceptionBlueprintInfo;
	PerceptionComponent->GetActorsPerception(Actor,ActorPerceptionBlueprintInfo);

	TSubclassOf<UAISense> SightSenseClass = UAISense_Sight::StaticClass();
	TSubclassOf<UAISense> HearingSenseClass = UAISense_Hearing::StaticClass();
	TSubclassOf<UAISense> DamageSenseClass = UAISense_Damage::StaticClass();
	
	for (FAIStimulus AIStimulas : ActorPerceptionBlueprintInfo.LastSensedStimuli)
	{
		TSubclassOf<UAISense> SenseClass = UAIPerceptionSystem::GetSenseClassForStimulus(this, AIStimulas);
		
		CanSenseActorData Local_CanSenseActorData;
		Local_CanSenseActorData.Stimulus = AIStimulas;
		if (Sense == EAISense::EAIS_Sight)
		{
			if (SenseClass == SightSenseClass)
			{
				Local_CanSenseActorData.Sensed = AIStimulas.WasSuccessfullySensed();
				return Local_CanSenseActorData;
			}
		}
		else if (Sense == EAISense::EAIS_Hearing)
		{
			if (SenseClass == HearingSenseClass)
			{
				Local_CanSenseActorData.Sensed = AIStimulas.WasSuccessfullySensed();
				return Local_CanSenseActorData;
			}
		}
		else if (Sense == EAISense::EAIS_Damage)
		{
			if (SenseClass == DamageSenseClass)
			{
				Local_CanSenseActorData.Sensed = AIStimulas.WasSuccessfullySensed();
				return Local_CanSenseActorData;
			}
		}
	}
	CanSenseActorData CanSenseActorData;
	return CanSenseActorData;
}

void AAIControllerBase::HandleSightSense(AActor* SensedActor)
{
	SetStateAsAttacking(SensedActor);
}

void AAIControllerBase::HandleHearingSense(FVector SoundOrigin_Loc)
{
}

void AAIControllerBase::HandleDamageSense()
{
}

void AAIControllerBase::SetStateAsAttacking(AActor* AttackTarget)
{
}

void AAIControllerBase::SetStateAsPassive()
{
}
