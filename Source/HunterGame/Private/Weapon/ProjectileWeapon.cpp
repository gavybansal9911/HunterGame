// Hunter Game by Gamer Guru.


#include "Weapon/ProjectileWeapon.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Weapon/Projectile.h"

void AProjectileWeapon::Shoot(const FVector& HitTarget) const
{
	Super::Shoot(HitTarget);
	APawn* InstigatorPawn = Cast<APawn>(GetOwner());
	if (const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName(FName("MuzzleFlash")))
	{
		FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
		FVector ToTarget = HitTarget - SocketTransform.GetLocation();    // Vector pointing towards HitTarget (From muzzle flash socket to hit location from TraceUnderCrosshair)
		FRotator TargetRotation = ToTarget.Rotation();
		if (ProjectileClass && InstigatorPawn)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = GetOwner();   // The Actor owning the weapon will own the projectile
			SpawnParameters.Instigator = InstigatorPawn;
			if (GetWorld())
			{
				GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SocketTransform.GetLocation(), TargetRotation, SpawnParameters);
			}
		}
	}
}
