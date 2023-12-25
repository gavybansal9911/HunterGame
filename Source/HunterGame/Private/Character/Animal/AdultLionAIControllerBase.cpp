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
	
	//OwnerLionCharacter = Cast<ALion>(GetPawn());
	OwnerLionCharacter = Cast<ALion>(OwnerAnimalCharacter);
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

	if (!OwnerLionCharacter) return;
	
	if (OwnerLionCharacter->IsLookingForFood())
	{
		Actor->ActorHasTag(FName("LionFood"));
		OwnerLionCharacter->SetAnimalStateAsHunting();
		GEngine->AddOnScreenDebugMessage(-1, 123.f, FColor::Cyan, FString("Hunting animals"));
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
