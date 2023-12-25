// Hunter Game by Gamer Guru.


#include "Component/AnimalSurvivalComponent.h"
#include "Character/Animal/BaseAnimal.h"

UAnimalSurvivalComponent::UAnimalSurvivalComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAnimalSurvivalComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAnimalSurvivalComponent::Init_Attributes()
{
	Init_Health();
	Init_Stamina();

	OnAttributesSet();
}

void UAnimalSurvivalComponent::Init_Health()
{
	MaxHealth = 100.f;
	Health = 100.f;
}

void UAnimalSurvivalComponent::Init_Stamina()
{
	MaxStamina = 100.f;
	Stamina = 100.f;
}

void UAnimalSurvivalComponent::OnAttributesSet()
{
	Init_AnimalMood();
}

void UAnimalSurvivalComponent::Init_AnimalMood()
{
	if (!OwnerAnimalCharacter) return;
	OwnerAnimalCharacter->GetWorldTimerManager().SetTimer(UpdateAnimalMoodTimerHandle, this, &UAnimalSurvivalComponent::UpdateAnimalMood, 2.f, true, 2.f);
}

void UAnimalSurvivalComponent::UpdateAnimalMood()
{
	if (!OwnerAnimalCharacter) return;
	
	if (HungerFactor > OwnerAnimalCharacter->GetAnimalHungerLimit())
	{
		OwnerAnimalCharacter->SetAnimalMood(EAnimalMood::EAM_Hungry);
		MoodAlpha = HungerFactor;
	}
	else if (AggressionFactor > OwnerAnimalCharacter->GetAnimalAggressionLimit())
	{
		OwnerAnimalCharacter->SetAnimalMood(EAnimalMood::EAM_Aggressive);
		MoodAlpha = AggressionFactor;
	}
	else if (FearFactor > OwnerAnimalCharacter->GetAnimalFearLimit())
	{
		OwnerAnimalCharacter->SetAnimalMood(EAnimalMood::EAM_Scared);
		MoodAlpha = FearFactor;
	}
	else
	{
		OwnerAnimalCharacter->SetAnimalMood(EAnimalMood::EAM_Normal);
		MoodAlpha = 1.f;
	}
}

void UAnimalSurvivalComponent::DecreaseAnimalHungerFactor_Start()
{
	if (!OwnerAnimalCharacter) return;

	OwnerAnimalCharacter->GetWorldTimerManager().SetTimer(DecreaseAnimalHungerFactorTimerHandle,
		this, &UAnimalSurvivalComponent::DecreaseAnimalHungerFactor_Update, 0.5f, true);
}

void UAnimalSurvivalComponent::DecreaseAnimalAggressionFactor_Start()
{
	if (!OwnerAnimalCharacter) return;
	
	OwnerAnimalCharacter->GetWorldTimerManager().SetTimer(DecreaseAnimalAggressionFactorTimerHandle,
		this, &UAnimalSurvivalComponent::DecreaseAnimalAggressionFactor_Update, 0.5f, true);
}

void UAnimalSurvivalComponent::DecreaseAnimalFearFactor_Start()
{
	if (!OwnerAnimalCharacter) return;

	OwnerAnimalCharacter->GetWorldTimerManager().SetTimer(DecreaseAnimalFearFactorTimerHandle,
		this, &UAnimalSurvivalComponent::DecreaseAnimalFearFactor_Update, 0.5f, true);
}

void UAnimalSurvivalComponent::DecreaseAnimalHungerFactor_Update()
{
	HungerFactor = FMath::Clamp(HungerFactor - 0.2f, 0.f, 1.f);
	if (HungerFactor == 0.f)
	{
		DecreaseAnimalHungerFactor_Clear();
	}
}

void UAnimalSurvivalComponent::DecreaseAnimalAggressionFactor_Update()
{
	AggressionFactor = FMath::Clamp(AggressionFactor - 0.2f, 0.f, 1.f);
	if (AggressionFactor == 0.f)
	{
		DecreaseAnimalAggressionFactor_Clear();
	}
}

void UAnimalSurvivalComponent::DecreaseAnimalFearFactor_Update()
{
	FearFactor = FMath::Clamp(FearFactor - 0.2f, 0.f, 1.f);
	if (FearFactor == 0.f)
	{
		DecreaseAnimalFearFactor_Clear();
	}
}

void UAnimalSurvivalComponent::DecreaseAnimalHungerFactor_Clear()
{
	if (OwnerAnimalCharacter)
	{
		OwnerAnimalCharacter->GetWorldTimerManager().ClearTimer(DecreaseAnimalHungerFactorTimerHandle);
	}
}

void UAnimalSurvivalComponent::DecreaseAnimalAggressionFactor_Clear()
{
	if (OwnerAnimalCharacter)
	{
		OwnerAnimalCharacter->GetWorldTimerManager().ClearTimer(DecreaseAnimalAggressionFactorTimerHandle);
	}
}

void UAnimalSurvivalComponent::DecreaseAnimalFearFactor_Clear()
{
	if (OwnerAnimalCharacter)
	{
		OwnerAnimalCharacter->GetWorldTimerManager().ClearTimer(DecreaseAnimalFearFactorTimerHandle);
	}
}

void UAnimalSurvivalComponent::ApplyDamage(float InDamageAmount)
{
	GEngine->AddOnScreenDebugMessage(-1, 34.f, FColor::Yellow, FString::Printf(TEXT("%f - %f"), Health, InDamageAmount));
	Health = FMath::Clamp(Health - InDamageAmount, 0.f, MaxHealth);
	if (Health == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 34.f, FColor::Yellow, FString("Animal is dead"));
		// Death
	}
}
