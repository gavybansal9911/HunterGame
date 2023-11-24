// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HunterPlayerController.generated.h"

class AHunterHUD;

/**
 * 
 */
UCLASS()
class HUNTERGAME_API AHunterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void SetHUDHealth(float Health, float MaxHealth);
	void SetHUDWeaponAmmo(int32 AmmoAmount);

protected:
	virtual void BeginPlay() override;
    
private:
	UPROPERTY()
    AHunterHUD* HunterHUD;
};
