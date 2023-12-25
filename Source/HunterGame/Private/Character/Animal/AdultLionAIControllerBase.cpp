// Hunter Game by Gamer Guru.


#include "Character/Animal/AdultLionAIControllerBase.h"
#include "Character/Animal/Lion.h"

AAdultLionAIControllerBase::AAdultLionAIControllerBase()
{
}

void AAdultLionAIControllerBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AAdultLionAIControllerBase::Init_Controller()
{
	Super::Init_Controller();
	
	OwnerLionCharacter = Cast<ALion>(GetPawn());
	if (OwnerLionCharacter)
	{
		OnOwnerAnimalCharacterSet();
	}
}

void AAdultLionAIControllerBase::OnOwnerAnimalCharacterSet()
{
	Super::OnOwnerAnimalCharacterSet();
}

void AAdultLionAIControllerBase::HandleSightSense(AActor* Actor)
{
	Super::HandleSightSense(Actor);

	if (OwnerLionCharacter)
	{
		if (OwnerLionCharacter->IsLookingForFood())
		{
			Actor->ActorHasTag(FName("LionFood"));
			OwnerLionCharacter->SetAnimalStateAsHunting();
			// Set state as hunting and set target actor
		}
	}
}

void AAdultLionAIControllerBase::HandleHearingSense(FVector SoundOrigin_Loc)
{
	Super::HandleHearingSense(SoundOrigin_Loc);
}

void AAdultLionAIControllerBase::HandleDamageSense(AActor* Actor)
{
	Super::HandleDamageSense(Actor);
}
