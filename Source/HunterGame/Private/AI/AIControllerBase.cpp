// Hunter Game by Gamer Guru.


#include "AI/AIControllerBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionSystem.h"
#include "AI/EnemyBase.h"
#include "Character/BaseCharacter.h"

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
	OwnerAIEnemy = Cast<AEnemyBase>(GetPawn());
	if (Blackboard)
	{
		Blackboard->SetValueAsEnum(BB_AIState_KeyName, 1);
	}
	
}

void AAIControllerBase::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	CanSenseActorData SenseActorData;
	
	for (AActor* Actor : UpdatedActors)
	{
		// Sensed Sight?
		SenseActorData = CanSenseActor(Actor, EAIPerceptionSense::EAIS_Sight);
		if (SenseActorData.Sensed)
		{
			HandleSightSense(Actor);
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, FString("Sight Triggered"));
		}

		// Sensed Hearing?
		SenseActorData = CanSenseActor(Actor, EAIPerceptionSense::EAIS_Hearing);
		if (SenseActorData.Sensed)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, FString("Hearing Triggered"));
			HandleHearingSense(SenseActorData.Stimulus.StimulusLocation);
		}

		// Sensed Damage?
		SenseActorData = CanSenseActor(Actor, EAIPerceptionSense::EAIS_Damage);
		if (SenseActorData.Sensed)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, FString("Damage Triggered"));
			HandleDamageSense();
		}
	}
}

CanSenseActorData AAIControllerBase::CanSenseActor(AActor* Actor, EAIPerceptionSense Sense)
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
		if (Sense == EAIPerceptionSense::EAIS_Sight)
		{
			if (SenseClass == SightSenseClass)
			{
				Local_CanSenseActorData.Sensed = AIStimulas.WasSuccessfullySensed();
				return Local_CanSenseActorData;
			}
		}
		else if (Sense == EAIPerceptionSense::EAIS_Hearing)
		{
			if (SenseClass == HearingSenseClass)
			{
				Local_CanSenseActorData.Sensed = AIStimulas.WasSuccessfullySensed();
				return Local_CanSenseActorData;
			}
		}
		else if (Sense == EAIPerceptionSense::EAIS_Damage)
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
	if (Cast<ABaseCharacter>(SensedActor))
	{
		Blackboard->SetValueAsObject(FName("TargetActor"), SensedActor);
		SetStateAsChasing(SensedActor);
	}
}

void AAIControllerBase::HandleHearingSense(FVector SoundOrigin_Loc)
{
}

void AAIControllerBase::HandleDamageSense()
{
}

void AAIControllerBase::SetStateAsPassive()
{
	if (Blackboard == nullptr) return;
	AIState = EAIState::EAIS_Passive;
	Blackboard->SetValueAsEnum(BB_AIState_KeyName, 1);
	ClearFocus(EAIFocusPriority::Default);
}

void AAIControllerBase::SetStateAsChasing(AActor* TargetActor)
{
	if (Blackboard == nullptr) return;
	AIState = EAIState::EAIS_Chasing;
	Blackboard->SetValueAsEnum(BB_AIState_KeyName, 3);
	ClearFocus(EAIFocusPriority::Default);
}

void AAIControllerBase::SetStateAsAttacking(AActor* TargetActor)
{
	if (Blackboard == nullptr) return;
	AIState = EAIState::EAIS_Attacking;
	Blackboard->SetValueAsEnum(BB_AIState_KeyName, 4);
	SetFocus(TargetActor);
}
