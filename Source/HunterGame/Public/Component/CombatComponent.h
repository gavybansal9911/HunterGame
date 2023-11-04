// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


class AWeapon;
class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUNTERGAME_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	friend ABaseCharacter;
	UCombatComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	/** Player Reference **/
	UPROPERTY()
	ABaseCharacter* HunterCharacter;
	/** Player Reference **/

	/** Combat **/
	void EquipWeapon(AWeapon* Weapon);
	void AttachToActor(const ACharacter* InParent, AActor* ActorToAttach, const FName SocketName);
	/** Combat **/

protected:
	virtual void BeginPlay() override;
	void SetAiming(bool bAiming);

	UFUNCTION(Server, Reliable)
	void ServerSetAiming(bool bAiming);

private:
	/** Character Owned Weapon Reference **/
	UPROPERTY()
	AWeapon* WeaponInHand;

	UPROPERTY()
	AWeapon* PrimaryWeapon;

	UPROPERTY()
	AWeapon* SecondaryWeapon;
	/** Character Owned Weapon Reference **/

	/** State Reference **/
	UPROPERTY(Replicated)
	bool bIsCombatEnabled;
	
	UPROPERTY(Replicated)
	bool bIsAiming;
	/** State Reference **/

public:
	FORCEINLINE void SetIsCombatEnabled(bool bCombatEnabled) {bIsCombatEnabled = bCombatEnabled;}
	FORCEINLINE AWeapon* GetWeaponInHand() const {return WeaponInHand;}
	FORCEINLINE void SetWeaponInHand(AWeapon* InWeapon) {WeaponInHand = InWeapon;}
};
