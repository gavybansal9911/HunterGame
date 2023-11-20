// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;
class UParticleSystem;
class UParticleSystemComponent;
class USoundCue;

UCLASS()
class HUNTERGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;  // We will spawn impact particle and impact sound for clients in Destroyed function because this function is already replicated and we can take advantage of it

protected:
	virtual void BeginPlay() override;

	// Hit Event
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastOnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Damage **/
	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage = 20.f;
	/** Damage **/
	
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> CollisionBox;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	/** Visuals and Sounds effects **/
	UPROPERTY(EditAnywhere, Category = "FX")
	UParticleSystem* Tracer;

	UPROPERTY()
	UParticleSystemComponent* TracerComponent;

	UPROPERTY(EditAnywhere, Category = "FX")
	UParticleSystem* ImpactParticle;

	UPROPERTY(EditAnywhere, Category = "FX")
	UParticleSystem* ImpactObstacleParticles;
 
	UPROPERTY(EditAnywhere, Category = "FX")
	UParticleSystem* ImpactCharacterParticles;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundCue* ImpactSound;
	/** Visuals and Sounds effects **/
};
