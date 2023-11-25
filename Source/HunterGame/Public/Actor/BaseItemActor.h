// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItemActor.generated.h"

class USphereComponent;

UCLASS()
class HUNTERGAME_API ABaseItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseItemActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	TObjectPtr<USphereComponent> AreaSphere;
};
