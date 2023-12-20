// Hunter Game by Gamer Guru.


#include "Character/Animal/Elephant_GroupLeader.h"
#include "Character/Animal/Elephant_Follower.h"

AElephant_GroupLeader::AElephant_GroupLeader()
{
	PrimaryActorTick.bCanEverTick = false;

	Tags.AddUnique(FName("GroupLeader"));
	Tags.AddUnique(FName("Elephant_GroupLeader"));
}

void AElephant_GroupLeader::BeginPlay()
{
	Super::BeginPlay();
	Spawn_Group();
}

void AElephant_GroupLeader::Tick(float DeltaSeconds)
{
	// bCanEverTick is set to false.
	Super::Tick(DeltaSeconds);
}

void AElephant_GroupLeader::Spawn_Group()
{
	if (ElephantFollowerCharacter_Class == nullptr) return;
	if (GroupSize - 1 <= 0) return;

	for (int i = 1; i <= GroupSize - 1; i++)
	{
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
		const float RandomScale3D = FMath::FRandRange(Scale3DMin, Scale3DMax);
		SpawnTransform.SetScale3D(FVector(RandomScale3D, RandomScale3D, RandomScale3D));

		// ActorSpawnParams
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Instigator = this;
		ActorSpawnParameters.Owner = this;
		ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// Spawn actor
		AElephant_Follower* Elephant_Follower = GetWorld()->SpawnActor<AElephant_Follower>(ElephantFollowerCharacter_Class, SpawnTransform, ActorSpawnParameters);
		if (Elephant_Follower)
		{
			GroupFollowers.Add(Elephant_Follower);
		}
	}

	OnGroupSpawned();
}

void AElephant_GroupLeader::OnGroupSpawned()
{
	for (auto Follower : GroupFollowers)
	{
		Follower->SpawnDefaultController();
	}
}
