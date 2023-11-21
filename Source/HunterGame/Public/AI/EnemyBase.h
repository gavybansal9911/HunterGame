// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "AI_Types.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

class USphereComponent;
class UBehaviorTree;
class AAIControllerBase;
class UAnimMontage;

UCLASS()
class HUNTERGAME_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;  // Called when the this character is possessed

	/** Combat **/
	void GetInCombat(AActor* TargetActor);
	void GetInCombat_Melee(AActor* TargetActor);

	void Attack();
	void Attack_Melee();
	/** Combat **/

protected:
	virtual void BeginPlay() override;

	/** Overlap CallBacks **/
	UFUNCTION()
	virtual void OnAttackSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void OnAttackSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	/** Overlap CallBacks **/
	
	/** Timer CallBacks **/
	void MeleeCombatChaseTimer();
	void MeleeAttackTimer();
	/** Timer CallBacks **/
	
protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY()
	TObjectPtr<AAIControllerBase> AIController;

	/** Enemy States **/
	EAIMovementMode AIMovementMode = EAIMovementMode::EMM_Idle;
	EEquippedWeaponType EquippedWeaponType = EEquippedWeaponType::EEWT_None;
	/** Enemy States **/

	/** Animation **/
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* DaggerAttackMontage;
	/** Animation **/

	/* Range */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> MeleeAttackSphere;
	/* Range */

private:
	FTimerHandle MeleeCombatChaseTimerHandle;
	FTimerHandle MeleeAttackTimerHandle;
};
