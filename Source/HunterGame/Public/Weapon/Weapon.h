// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "WeaponTypes.h"
#include "Component/InventoryTypes.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractInterface.h"
#include "Weapon.generated.h"

class AWeaponAmmo;
class ABulletShell;
class USphereComponent;
class UAnimationAsset;
class UTexture2D;
class UAnimMontage;
class ABaseCharacter;
class AHunterPlayerController;

UCLASS()
class HUNTERGAME_API AWeapon : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	AWeapon();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void OnRep_Owner() override;
	virtual void Tick(float DeltaTime) override;

	/** Interface **/
	virtual FString LookAt() override;
	virtual void InteractWith(ABaseCharacter* PlayerCharacter) override;
	/** Interface **/

	void SetHUDWeaponAmmo();
	
	/** Components **/
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> AreaSphere;
	/** Components **/

	/** Combat **/
	virtual void Shoot(const FVector& HitTarget);
	void AddAmmoToWeapon(int32 AmmoToAdd);
	/** Combat **/

	/** Textures for the weapon crosshair **/
	UPROPERTY(EditAnywhere, Category = "Crosshair")
	UTexture2D* CrosshairCenter;
	
	UPROPERTY(EditAnywhere, Category = "Crosshair")
	UTexture2D* CrosshairLeft;
	
	UPROPERTY(EditAnywhere, Category = "Crosshair")
	UTexture2D* CrosshairRight;	

	UPROPERTY(EditAnywhere, Category = "Crosshair")
	UTexture2D* CrosshairTop;
	
	UPROPERTY(EditAnywhere, Category = "Crosshair")
	UTexture2D* CrosshairBottom;
	/** Textures for the weapon crosshair **/

	/** Animation **/
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* TakeOutWeaponMontage;
	
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* PutWeaponInMontage;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* ReloadMontage;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* WeaponShootMontage;
	/** Animation **/

protected:
	virtual void BeginPlay() override;

	/** Overlap Triggers **/
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	/** Overlap Triggers **/

	/** Effects **/
	virtual void HighlightWeapon();      // Post process highlight
	virtual void UnHighlightWeapon();       // Post process unhighlight
	/** Effects **/

private:
	/** Reference **/
	UPROPERTY()
	ABaseCharacter* OwnerCharacter;
	UPROPERTY()
	AHunterPlayerController* OwnerController;
	/** Reference **/
	
	/** Attachment Properties **/
	UPROPERTY(EditAnywhere, Category = "Attachment")
	FName OutHandAttachSocketName;
	UPROPERTY(EditAnywhere, Category = "Attachment")
	FName InHandAttachSocketName;
	/** Attachment Properties **/

	/** Weapon Properties && Status **/
	FItemData WeaponData;
	
	UPROPERTY(EditAnywhere, Category = "Properties")
	bool bAutomatic;
	
	UPROPERTY(EditAnywhere, Category = "Properties")
	float AutoFireDelay = 0.1f;
	
	UPROPERTY(Replicated)
	EWeaponState WeaponState = EWeaponState::EWS_Unattached;

	UPROPERTY(EditAnywhere, Category = "Properties")
	EWeaponClass WeaponClass = EWeaponClass::EWC_Max;

	UPROPERTY(EditAnywhere, Category = "Properties")
	EWeaponName WeaponName = EWeaponName::EWN_Rifle;
	
	EAttachmentStatus AttachmentStatus = EAttachmentStatus::EAS_Max;

	UPROPERTY(EditAnywhere, Category = "Properties")
	EWeaponType WeaponType = EWeaponType::EWC_Ranged;
	/** Weapon Properties && Status **/

	/** Weapon Properties **/
	UPROPERTY(EditAnywhere, Category = "Properties")
	TSubclassOf<ABulletShell> BulletShellClass;

	UPROPERTY(EditAnywhere, Category = "Properties")
	bool bNeedsFABRIK = true;
	
	UPROPERTY(EditAnywhere, Category = "Properties")
	bool bApplyFABRIKOnlyWhenAiming = false;

	UPROPERTY(EditAnywhere, Category = "Properties")
	float WeaponRange = 2000.f;
	/** Weapon Properties **/

	/** Weapon Animation **/
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimationAsset* FireAnimationAsset;    // Weapon Animation Sequence reference
	/** Weapon Animation **/

	/** Ammo **/
	UPROPERTY(EditAnywhere, Category = "Ammo")
	TSubclassOf<AWeaponAmmo> WeaponAmmoClass;

	int32 GetAmmoInInventory();
	
	void SpendRound();
	
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_Ammo, Category = "Ammo")
	int32 Ammo;
	
	UPROPERTY(EditAnywhere, Category = "Ammo")
	int32 MagazineSize;
	/** Ammo **/

	/** Rep Notifies **/
	UFUNCTION()
	void OnRep_Ammo();
	/** Rep Notifies **/

public:
	FORCEINLINE FName GetInHandAttachSocketName() const {return InHandAttachSocketName;}
	FORCEINLINE FName GetOutHandAttachSocketName() const {return OutHandAttachSocketName;}
	FORCEINLINE EWeaponState GetWeaponState() const {return WeaponState;}
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const {return WeaponMesh;}
	FORCEINLINE EWeaponClass GetWeaponClass() const {return WeaponClass;}
	FORCEINLINE EWeaponType GetWeaponType() const {return WeaponType;}
	FORCEINLINE EAttachmentStatus GetWeaponAttachmentStatus() const {return AttachmentStatus;}
	FORCEINLINE float GetWeaponRange() const {return WeaponRange;}
	FORCEINLINE float GetAutoFireDelay() const {return AutoFireDelay;}
	FORCEINLINE bool IsWeaponAutomatic() const {return bAutomatic;}
	FORCEINLINE int32 GetAmmoInWeapon() const {return Ammo;}
	FORCEINLINE int32 GetMagazineSize() const {return MagazineSize;}
	FORCEINLINE TSubclassOf<AWeaponAmmo> GetWeaponAmmoClass() const {return WeaponAmmoClass;}
	FORCEINLINE EWeaponName GetWeaponName() const {return WeaponName;}
	FORCEINLINE bool ShouldApplyFABRIK() const {return bNeedsFABRIK;}
	FORCEINLINE bool ShouldApplyFABRIKOnlyWhenAiming() const {return bApplyFABRIKOnlyWhenAiming;}
	bool IsMagazineEmpty() const;

	FORCEINLINE void SetWeaponState(const EWeaponState NewWeaponState) {WeaponState = NewWeaponState;}
	FORCEINLINE void SetWeaponAttachmentStatus(const EAttachmentStatus NewWeaponAttachmentStatus) {AttachmentStatus = NewWeaponAttachmentStatus;}
	FORCEINLINE void SetAmmoInWeapon(const int32 InAmmo) {Ammo = InAmmo;}
};
