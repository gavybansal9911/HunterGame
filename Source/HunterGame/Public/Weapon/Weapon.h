// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "WeaponTypes.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractInterface.h"
#include "Weapon.generated.h"

class USphereComponent;
class UAnimationAsset;

UCLASS()
class HUNTERGAME_API AWeapon : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	AWeapon();
	virtual void Tick(float DeltaTime) override;

	/** Interface **/
	virtual FString LookAt() override;;
	virtual void InteractWith(ABaseCharacter* HunterCharacter) override;
	/** Interface **/

	/** Components **/
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> AreaSphere;
	/** Components **/

	/** Shooting **/
	void Shoot() const;
	/** Shooting **/

protected:
	virtual void BeginPlay() override;

	/** Overlap Triggers **/
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	/** Overlap Triggers **/

private:
	/** Attachment Properties **/
	UPROPERTY(EditAnywhere, Category = "Attachment")
	FName OutHandAttachSocketName;
	UPROPERTY(EditAnywhere, Category = "Attachment")
	FName InHandAttachSocketName;
	/** Attachment Properties **/

	/** Weapon Properties && Status **/
	EWeaponName WeaponName = EWeaponName::EWN_Rifle;
	EWeaponClass WeaponClass = EWeaponClass::EWC_Max;
	EWeaponState WeaponState = EWeaponState::EWS_Unattached;
	EAttachmentStatus AttachmentStatus = EAttachmentStatus::EAS_Max;
	/** Weapon Properties && Status **/

	/** Animation **/
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimationAsset* FireAnimationAsset;    // Weapon Animation Sequence reference
	/** Animation **/

public:
	FORCEINLINE FName GetInHandAttachSocketName() const {return InHandAttachSocketName;}
	FORCEINLINE FName GetOutHandAttachSocketName() const {return OutHandAttachSocketName;}
	FORCEINLINE EWeaponState GetWeaponState() const {return WeaponState;}
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const {return WeaponMesh;}

	FORCEINLINE void SetWeaponState(const EWeaponState NewWeaponState) {WeaponState = NewWeaponState;}
	FORCEINLINE void SetWeaponAttachmentStatus(const EAttachmentStatus NewWeaponAttachmentStatus) {AttachmentStatus = NewWeaponAttachmentStatus;}
};
