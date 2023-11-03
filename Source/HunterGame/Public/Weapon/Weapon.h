// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "WeaponTypes.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractInterface.h"
#include "Weapon.generated.h"

class USphereComponent;

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

	/** Interaction **/
	void Equip(const ABaseCharacter* HunterCharacter);
	void AttachToActor(const ACharacter* InParent, FName SocketName);
	/** Interaction **/

protected:
	virtual void BeginPlay() override;

	/** Overlap Triggers **/
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	/** Overlap Triggers **/
	
	/** Components **/
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> AreaSphere;
	/** Components **/

private:
	/** Attachment Properties **/
	UPROPERTY(EditAnywhere, Category = "Attachment")
	FName OutHandAttachSocketName;
	UPROPERTY(EditAnywhere, Category = "Attachment")
	FName InHandAttachSocketName;
	/** Attachment Properties **/

	/** Weapon Properties && Status **/
	EWeaponClass WeaponClass = EWeaponClass::EWC_Max;
	EWeaponState WeaponState = EWeaponState::EWS_Unattached;
	EAttachmentStatus AttachmentStatus = EAttachmentStatus::EAS_Max;
	/** Weapon Status **/
};
