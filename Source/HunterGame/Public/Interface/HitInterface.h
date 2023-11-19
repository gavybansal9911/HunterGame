// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HitInterface.generated.h"

UINTERFACE(MinimalAPI)
class UHitInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HUNTERGAME_API IHitInterface
{
	GENERATED_BODY()

public:
	virtual void GetHit();
	virtual void PlayHitReactMontage(ACharacter* HitCharacter, UAnimMontage* Montage, FName SectionName = FName("Default"));
};
