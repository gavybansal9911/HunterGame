// Hunter Game by Gamer Guru.


#include "AI/EnemyGroupLeader_Base.h"
#include "Actor/Enemy_Group_Manager.h"
#include "AI/EnemyGroupMember_Base.h"

AEnemyGroupLeader_Base::AEnemyGroupLeader_Base()
{
	PrimaryActorTick.bCanEverTick = false;

	Tags.Add(FName("PoacherLeader"));
	Tags.Add(FName("PoacherGroupLeader"));
	Tags.Add(FName("PoacherTeamLeader"));
	
	bIsLeader = true;
	
	// Initialize poacher group array
	PoacherGroupMembersToSpawn.SetNum(0);
}

void AEnemyGroupLeader_Base::BeginPlay()
{
	Super::BeginPlay();
	Init_PoacherGroup();
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

void AEnemyGroupLeader_Base::Init_PoacherGroup()
{
	for (int i = 0; i < PoacherGroupMembersToSpawn.Num(); i++)
	{
		if (PoacherGroupMembersToSpawn[i] == nullptr) {continue;} //{goto SKIP_SPAWN;}

		// Transform
		FTransform SpawnTransform;

		// Location
		const float RandomAngle = FMath::FRandRange(0.0f, 2.0f * PI);
		const float RandomRadius = FMath::RandRange(0.0f, GroupAreaCoverage);
		const float RandomX = RandomRadius * FMath::Cos(RandomAngle);
		const float RandomY = RandomRadius * FMath::Sin(RandomAngle);
		FVector RandomLocation = GetActorLocation() + FVector(RandomX, RandomY, 0.0f);
		SpawnTransform.SetLocation(RandomLocation);

		// Rotation
		FRotator RandomYawRotation = GetActorRotation();
		RandomYawRotation.Yaw = FMath::FRandRange(0.f, 360.f);
		SpawnTransform.Rotator() = RandomYawRotation;

		// Scale3D
		const float RandomScale3D = FMath::FRandRange(0.9f, 1.f);
		SpawnTransform.SetScale3D(FVector(RandomScale3D, RandomScale3D, RandomScale3D));
		
		// Actor Spawn Params
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Instigator = this;
		ActorSpawnParameters.Owner = this;
		ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		
		AEnemyGroupMember_Base* PoacherMember = GetWorld()->SpawnActor<AEnemyGroupMember_Base>(PoacherGroupMembersToSpawn[i], SpawnTransform, ActorSpawnParameters);
		if (PoacherMember)
		{
			PoacherGroupMembers_Alive.Add(PoacherMember);
			EnemyGroupManager->Initial_GroupSize++;
			EnemyGroupManager->CurrentGroupSize++;
		}

		//SKIP_SPAWN:;
	}

	OnPoacherGroupSpawned();
}

void AEnemyGroupLeader_Base::OnPoacherGroupSpawned()
{
	for (AEnemyGroupMember_Base* PoacherMember : PoacherGroupMembers_Alive)
	{
		if (PoacherMember == nullptr) return;
		
		PoacherMember->SetLeader(this);
		PoacherMember->SetGroupId(GroupId);
		PoacherMember->SetGroupManager(EnemyGroupManager);
		PoacherMember->SpawnDefaultController();
		PoacherMember->OnIndirectSpawn();
		EnemyGroupManager->Enemy_GroupLeader = this;
		EnemyGroupManager->NPC_Enemies.Add(PoacherMember);
		EnemyGroupManager->NPC_Enemies_GroupMembers.Add(PoacherMember);
	}
}

void AEnemyGroupLeader_Base::OnDeath()
{
	EnemyGroupManager->Enemy_GroupLeader = nullptr;
	EnemyGroupManager->NPC_Enemies.Remove(this);
	EnemyGroupManager->CurrentGroupSize--;
	Super::OnDeath();
}

void AEnemyGroupLeader_Base::OnGroupMemberDeath(AEnemyGroupMember_Base* MemberRef)
{
	if (MemberRef)
	{
		EnemyGroupManager->NPC_Enemies.Remove(MemberRef);
		EnemyGroupManager->NPC_Enemies_GroupMembers.Remove(MemberRef);
	}
	EnemyGroupManager->CurrentGroupSize--;
}
