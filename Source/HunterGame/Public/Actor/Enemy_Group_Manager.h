// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy_Group_Manager.generated.h"

class AEnemyGroupLeader_Base;
class AEnemyGroupMember_Base;
class AEnemyBase;

UCLASS()
class HUNTERGAME_API AEnemy_Group_Manager : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemy_Group_Manager();
	
	UPROPERTY(EditAnywhere, Category = "Data")
	int32 GroupId = -1;     // -1 if not managing any group

	UPROPERTY()
	AEnemyGroupLeader_Base* Enemy_GroupLeader;
	UPROPERTY()
	TArray<AEnemyBase*> NPC_Enemies;
	UPROPERTY()
	TArray<AEnemyGroupMember_Base*> NPC_Enemies_GroupMembers;

	int32 Initial_GroupSize = 0;
	int32 CurrentGroupSize = 0;
	
protected:
	virtual void BeginPlay() override;
};
