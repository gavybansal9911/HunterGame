// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Component/InventoryTypes.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractInterface.h"
#include "Shop.generated.h"

class UShopMenu;
class UWidgetComponent;
class UBoxComponent;

UCLASS()
class HUNTERGAME_API AShop : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	AShop();
	virtual void InteractWith(ABaseCharacter* PlayerCharacter) override;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category = "Shopkeeper")
	USkeletalMeshComponent* ShopkeeperMesh;

	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	UBoxComponent* OverlapBox;

	// On Overlap
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// On End Overlap
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	// Interact Widget
	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	UWidgetComponent* InteractWidget;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UShopMenu> ShopMenuUWClass;

	UPROPERTY()
	UShopMenu* ShopMenuUW;

	UPROPERTY(EditAnywhere, Category = "Content")
	TArray<FSlotData> ShopContent;
};
