// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUNTERGAME_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	friend ABaseCharacter;
	UInteractionComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Player Reference **/
	UPROPERTY()
	ABaseCharacter* PlayerCharacter;
	/** Player Reference **/

protected:
	virtual void BeginPlay() override;
	void Interact();
	void OnPlayerInteractWithAnimal(UAnimMontage* PlayerInteractWithAnimalAnimMontage);

private:
	UPROPERTY(VisibleAnywhere, Category = "Overlapping")
	TObjectPtr<AActor> OverlappingActor;

	UPROPERTY(VisibleAnywhere, Category = "Interaction Target")
	TObjectPtr<AActor> InteractionTargetActor;
	
public:
	FORCEINLINE AActor* GetOverlappingActor() const {return OverlappingActor;}
	FORCEINLINE void SetOverlappingActor(AActor* InActor) {OverlappingActor = InActor;}
	
	FORCEINLINE AActor* GetInteractionTargetActor() const {return InteractionTargetActor;}
	FORCEINLINE void SetInteractionTargetActor(AActor* InActor) {InteractionTargetActor = InActor;}
};
