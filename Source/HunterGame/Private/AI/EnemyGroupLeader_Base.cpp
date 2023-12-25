// Hunter Game by Gamer Guru.


#include "AI/EnemyGroupLeader_Base.h"

AEnemyGroupLeader_Base::AEnemyGroupLeader_Base()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemyGroupLeader_Base::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyGroupLeader_Base::Tick(float DeltaSeconds)
{
	// bCanEverTick is set to false.
	Super::Tick(DeltaSeconds);
}

void AEnemyGroupLeader_Base::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AEnemyGroupLeader_Base::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
