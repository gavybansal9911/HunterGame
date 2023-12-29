// Hunter Game by Gamer Guru.


#include "AI/EnemyGroupMember_Base.h"
#include "AI/AIControllerBase.h"
#include "AI/EnemyGroupLeader_Base.h"

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

void AEnemyGroupMember_Base::OnDeath()
{
	if (Leader)
	{
		Leader->OnGroupMemberDeath(this);
	}
	Super::OnDeath();
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

void AEnemyGroupMember_Base::OnLeaderStateChanged()
{
	if (!Leader) return;
	
	switch (Leader->GetAIState())
	{
		case EAIState::EAIS_None:
			break;
		case EAIState::EAIS_Passive:
			AIController->SetStateAsPassive();
			GEngine->AddOnScreenDebugMessage(-1, 43258.f, FColor::Blue, FString("Passive"));
			break;
		case EAIState::EAIS_Hunting:
			AIController->SetBBTargetActor(Leader->Get_TargetActor_BB());
			AIController->SetStateAsHunting(Leader->Get_TargetActor_BB());
			GEngine->AddOnScreenDebugMessage(-1, 43258.f, FColor::Blue, FString("Hunting"));
			break;
		case EAIState::EAIS_Investigating:
			AIController->SetStateAsInvestigating();
			break;
		case EAIState::EAIS_Chasing:
			AIController->SetBBTargetActor(Leader->Get_TargetActor_BB());
			AIController->SetStateAsChasing(Leader->Get_TargetActor_BB());
			GEngine->AddOnScreenDebugMessage(-1, 43258.f, FColor::Blue, FString("Chasing"));
			break;
		case EAIState::EAIS_Attacking:
			//AIController->SetBBTargetActor(Leader->Get_TargetActor_BB());
			//AIController->SetStateAsAttacking(Leader->Get_TargetActor_BB());
			GEngine->AddOnScreenDebugMessage(-1, 43258.f, FColor::Blue, FString("Attacking"));
			break;
		case EAIState::EAIS_Retreating:
			AIController->SetStateAsRetreating();
			break;
		case EAIState::EAIS_RunningAway:
			AIController->SetStateAsRunningAway();
			break;
		default:
			break;
	}
}
