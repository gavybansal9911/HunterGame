// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "ProjectileWeapon.generated.h"

class AProjectile;

/**
 * 
 */
UCLASS()
class HUNTERGAME_API AProjectileWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	virtual void Shoot(const FVector& HitTarget) override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Properties")
    TSubclassOf<AProjectile> ProjectileClass;
};
