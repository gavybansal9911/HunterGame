// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicalAnimation_C_Component.generated.h"


class UPhysicalAnimationComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUNTERGAME_API UPhysicalAnimation_C_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPhysicalAnimation_C_Component();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Init_Component();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	ACharacter* OwnerCharacter = nullptr;

	UPROPERTY()
	UPhysicalAnimationComponent* BasePhysicalAnimationComponent;

public:
	void SetOwnerCharacter(ACharacter* InCharacter) {OwnerCharacter = InCharacter;}
};
