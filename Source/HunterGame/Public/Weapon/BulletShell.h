// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletShell.generated.h"

class USoundCue;

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

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BulletShellMesh;

	UPROPERTY(EditAnywhere, Category = "Properties")
	float ShellEjectionImpulse = 10.f;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundCue* ShellSound;
};
