// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIEnemyCombatComponent.generated.h"


class AWeapon;
class AEnemyBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUNTERGAME_API UAIEnemyCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	friend AEnemyBase;
	UAIEnemyCombatComponent();

	/** Generic **/
	void PlayAnimMontage(UAnimMontage* AnimMontage, FName SectionName, bool bJumpToSection);
	/** Generic **/

protected:
	virtual void BeginPlay() override;
	
	virtual void Init_Weapon();
	virtual void ToggleWeapon();
	virtual void PlayToggleWeaponAnimMontage();
	virtual void ToggleWeaponAnimNotifyCallBack();
	
	virtual void EnableCombat();
	virtual void DisableCombat();

	void UpdateAttackRadius();

	void Aim();
	
	void Attack();
	
private:
	// Owner
	UPROPERTY()
	AEnemyBase* OwnerAIEnemy;
	
	// Weapon
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<AWeapon> WeaponClass;
	
	UPROPERTY()
	AWeapon* Weapon;

	/** Combat **/
	bool bIsAiming;
	/** Combat **/
};
