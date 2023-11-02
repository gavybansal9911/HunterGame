// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUNTERGAME_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	friend ABaseCharacter;
	UCombatComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	/** Player Reference **/
	UPROPERTY()
	ABaseCharacter* HunterCharacter;
	/** Player Reference **/

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE bool IsCombatEnabled() const {return true;}
};
