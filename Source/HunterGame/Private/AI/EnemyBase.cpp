// Hunter Game by Gamer Guru.


#include "AI/EnemyBase.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
