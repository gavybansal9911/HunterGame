// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "AI/EnemyBase.h"
#include "EnemyGroupLeader_Base.generated.h"

class AEnemyGroupMember_Base;

/**
 * 
 */
UCLASS()
class HUNTERGAME_API AEnemyGroupLeader_Base : public AEnemyBase
{
	GENERATED_BODY()

public:
	AEnemyGroupLeader_Base();
	virtual void Tick(float DeltaSeconds) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;
	
	/** Enemy Group **/
	virtual void Init_PoacherGroup();
	virtual void OnPoacherGroupSpawned();

	//UPROPERTY(EditAnywhere, Category = "PoacherGroup")
	//int NumberOfPoachers = 7;
	
	UPROPERTY(EditAnywhere, Category = "Poacher Group")
	TArray<TSubclassOf<AEnemyGroupMember_Base>> PoacherGroupMembersToSpawn;

	UPROPERTY()
	TArray<AEnemyGroupMember_Base*> PoacherGroupMembers_Alive;

	UPROPERTY(EditAnywhere, Category = "Poacher Group")
	float GroupAreaCoverage = 350.f;
	/** Enemy Group **/
};
