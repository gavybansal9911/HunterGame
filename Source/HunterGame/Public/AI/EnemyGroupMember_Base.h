// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "AI/EnemyBase.h"
#include "EnemyGroupMember_Base.generated.h"

class AEnemyGroupLeader_Base;
/**
 * 
 */
UCLASS()
class HUNTERGAME_API AEnemyGroupMember_Base : public AEnemyBase
{
	GENERATED_BODY()

public:
	AEnemyGroupMember_Base();
	virtual void Tick(float DeltaSeconds) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;

	void OnIndirectSpawn();

	virtual void OnLeaderStateChanged();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	AEnemyGroupLeader_Base* Leader;

public:
	FORCEINLINE AEnemyGroupLeader_Base* GetLeader() const {return Leader;}
	void SetLeader(AEnemyGroupLeader_Base* InNewLeader) {Leader = InNewLeader;}
};
