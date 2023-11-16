// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletShell.generated.h"

UCLASS()
class HUNTERGAME_API ABulletShell : public AActor
{
	GENERATED_BODY()
	
public:	
	ABulletShell();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BulletShellMesh;

	UPROPERTY(EditAnywhere, Category = "Properties")
	float ShellEjectionImpulse = 10.f;
};
