// Hunter Game by Gamer Guru.


#include "AI/EnemyGroupMember_Base.h"
#include "AI/AIControllerBase.h"

AEnemyGroupMember_Base::AEnemyGroupMember_Base()
{
	PrimaryActorTick.bCanEverTick = false;

	Tags.Add(FName("PoacherMember"));
	Tags.Add(FName("PoacherGroupMember"));
	Tags.Add(FName("PoacherTeamMember"));

	bIsLeader = false;
}

void AEnemyGroupMember_Base::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyGroupMember_Base::Tick(float DeltaSeconds)
{
	// bCanEverTick is set to false.
	Super::Tick(DeltaSeconds);
}

void AEnemyGroupMember_Base::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AEnemyGroupMember_Base::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AEnemyGroupMember_Base::OnIndirectSpawn()
{
	AIController->OnIndirectSpawn();
}
