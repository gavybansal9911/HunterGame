// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletShell.generated.h"

class USoundCue;
class USoundConcurrency;

UCLASS()
class HUNTERGAME_API ABulletShell : public AActor
{
	GENERATED_BODY()
	
public:	
	ABulletShell();

protected:
	virtual void BeginPlay() override;
	
	// Hit Event
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Bullet Shell Destroy Timer CallBack
	void DestroyBulletShell();

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BulletShellMesh;

	UPROPERTY(EditAnywhere, Category = "Properties")
	float ShellEjectionImpulse = 10.f;

	// After how much time bullet should destroy after hitting ground
	UPROPERTY(EditAnywhere, Category = "Properties")
	float BulletDestroyDelay = 1.f;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundCue* ShellSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundConcurrency* ShellSoundConcurrency;

	// Bullet Destroy Timer
	FTimerHandle BulletDestroyHandle;
};
