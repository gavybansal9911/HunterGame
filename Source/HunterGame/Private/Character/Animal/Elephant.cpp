// Hunter Game by Gamer Guru.


#include "Character/Animal/Elephant.h"

AElephant::AElephant()
{
	PrimaryActorTick.bCanEverTick = false;

	bLiveInGroups = true;
	
	ElephantTusksMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Elephant Tusks Mesh"));
	ElephantTusksMesh->SetupAttachment(GetMesh());
}

void AElephant::BeginPlay()
{
	Super::BeginPlay();
	if (bIsLeader)
	{
		InitializeGroup(GroupSize);
	}
}

void AElephant::Tick(float DeltaSeconds)
{
	// bCanEverTick is set to false.
	Super::Tick(DeltaSeconds);
}
