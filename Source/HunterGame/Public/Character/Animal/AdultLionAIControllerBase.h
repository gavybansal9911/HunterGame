// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Character/Animal/AnimalAIControllerBase.h"
#include "AdultLionAIControllerBase.generated.h"

class ALion;

/**
 * 
 */
UCLASS()
class HUNTERGAME_API AAdultLionAIControllerBase : public AAnimalAIControllerBase
{
	GENERATED_BODY()

public:
	friend ALion;
	AAdultLionAIControllerBase();
	virtual void PostInitializeComponents() override;

protected:
	virtual void Init_Controller() override;
	virtual void OnOwnerAnimalCharacterSet() override;
	
	virtual void HandleSightSense(AActor* Actor) override;
	virtual void HandleHearingSense(FVector SoundOrigin_Loc) override;
	virtual void HandleDamageSense(AActor* Actor) override;

private:
	// Owner
	UPROPERTY()
	ALion* OwnerLionCharacter = nullptr;
};
