// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractInterface.h"
#include "BaseItemActor.generated.h"

class ABaseInventoryItem;
class USphereComponent;

UCLASS()
class HUNTERGAME_API ABaseItemActor : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	ABaseItemActor();

	/** Interface **/
	virtual void InteractWith(ABaseCharacter* PlayerCharacter) override;
	/** Interface **/

protected:
	virtual void BeginPlay() override;

	/** Components **/
	UPROPERTY(VisibleAnywhere, Category = "Properties")
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	TObjectPtr<USphereComponent> AreaSphere;
	/** Components **/

	/** Overlap Trigger CallBacks **/
	UFUNCTION()                                                                                                                                                                                  
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);  
	UFUNCTION()                                                                                                                                                                                  
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);                                               
	/** Overlap Trigger CallBacks **/

	/** Effects **/
	virtual void HighlightActor();      // Post process highlight
	virtual void UnHighlightActor();       // Post process unhighlight
	/** Effects **/
};
