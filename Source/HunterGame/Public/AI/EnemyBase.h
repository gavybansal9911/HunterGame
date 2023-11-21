// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class HUNTERGAME_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	virtual void BeginPlay() override;

};
