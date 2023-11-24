// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/WeaponTypes.h"
#include "CombatComponent.generated.h"

#define TRACE_LENGTH 100000.f
#define IN_AIR_CROSSHAIR_SPREAD 1.f

class AWeapon;
class ABaseCharacter;
class AHunterPlayerController;
class AHunterHUD;

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

	UPROPERTY()
	AHunterPlayerController* HunterController;

	UPROPERTY()
	AHunterHUD* HunterHUD;
	/** Player Reference **/

	/** Combat **/
	void EquipWeapon(AWeapon* Weapon);
	void AttachToActor(const ACharacter* InParent, AActor* ActorToAttach, const FName SocketName);
	bool CheckIfWeaponWithSameClassIsEquipped(EWeaponClass WeaponClass);
	void TogglePrimaryWeaponAttachment();
	void ToggleSecondaryWeaponAttachment();
	void DisableCombat();
	void EnableCombat();
	/** Combat **/

protected:
	virtual void BeginPlay() override;
	/** Aiming **/
	void SetAiming(bool bAiming);

	UFUNCTION(Server, Reliable)
	void ServerSetAiming(bool bAiming);
	/** Aiming **/

	/** Shooting **/
	void ShootButtonPressed(bool bPressed);
	bool CanShoot();
	void Shoot();
	
	UFUNCTION(Server, Reliable)
	void ServerShoot(bool bShootPressed, const FVector_NetQuantize& TraceHitTarget);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastShoot(bool bShootPressed, const FVector_NetQuantize& TraceHitTarget);
	/** Shooting **/

	/** Weapon **/
	void OnTogglePrimaryWeaponButtonPressed();
	void OnToggleSecondaryWeaponButtonPressed();
	/** Weapon **/
	
	/** Hitting Targets **/
	void TraceUnderCrosshair(FHitResult& TraceHitResult);
	/** Hitting Targets **/

	/** HUD and Crosshair **/
	void SetHUDCrosshair(float DeltaTime);
	float CrosshairVelocityFactor;
	float CrosshairInAirFactor;
	float CrosshairAimFactor;
	float CrosshairShootFactor;
	/** UI **/
	
	/** Rep Notifies **/
	UFUNCTION()
	void OnRep_EquippedWeapon();
	UFUNCTION()
	void OnRep_PrimaryWeapon();
	UFUNCTION()
	void OnRep_SecondaryWeapon();
	/** Rep Notifies **/

private:
	/** Combat **/
	UPROPERTY(ReplicatedUsing = OnRep_EquippedWeapon)
	AWeapon* WeaponInHand;

	UPROPERTY(ReplicatedUsing = OnRep_PrimaryWeapon)
	AWeapon* PrimaryWeapon;

	UPROPERTY(ReplicatedUsing = OnRep_SecondaryWeapon)
	AWeapon* SecondaryWeapon;

	UPROPERTY(Replicated)
	bool bShootButtonPressed;

	// Hit Target Location
	FVector HitTarget;
	/** Combat **/

	/** State Reference **/
	UPROPERTY(Replicated)
	bool bIsCombatEnabled;
	
	UPROPERTY(Replicated)
	bool bIsAiming;
	/** State Reference **/

	/** Speed **/
	UPROPERTY(EditAnywhere, Category = "Movement Properties");
	float BaseWalkSpeed{600.f};
	UPROPERTY(EditAnywhere, Category = "Movement Properties");
	float AimWalkSpeed{400.f};
	/** Speed **/

	/** Automatic Fire **/
	FTimerHandle FireTimer;
	void StartFireTimer();
	void FireTimerFinished();
	/** Automatic Fire **/

	/** Other Properties **/
	bool bCanShoot = true;
	/** Other Properties **/

public:
	FORCEINLINE void SetIsCombatEnabled(bool bCombatEnabled) {bIsCombatEnabled = bCombatEnabled;}
	FORCEINLINE AWeapon* GetWeaponInHand() const {return WeaponInHand;}
	FORCEINLINE void SetWeaponInHand(AWeapon* InWeapon) {WeaponInHand = InWeapon;}
};
