// Hunter Game by Gamer Guru.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Stat_Types.h"
#include "StatsComponent.generated.h"

class AEnemyBase;
class ABaseCharacter;
class IHumanInterface;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUNTERGAME_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	friend IHumanInterface;
	friend ABaseCharacter;
	friend AEnemyBase;
	UStatsComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Vital **/
	void AddToCurrentHealth(float Amount);
	void AddToCurrentMaxHealth(float Amount);
	void AddToCurrentStamina(float Amount);
	void AddToCurrentMaxStamina(float Amount);
	/** Vital **/
	
protected:
	virtual void BeginPlay() override;
	virtual void Init_Attributes();

private:
	// Owner
	IHumanInterface* OwnerHuman;

	void Init_Attribute(FAttributeData& AttributeData, float BaseValue, float CurrentValue);
	
	UPROPERTY(ReplicatedUsing = OnRep_Health, EditAnywhere, Category = "Vital Attributes")
	FAttributeData Health_Data;
	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth, EditAnywhere, Category = "Vital Attributes")
	FAttributeData MaxHealth_Data;

	UPROPERTY(ReplicatedUsing = OnRep_Stamina, EditAnywhere, Category = "Vital Attributes")
	FAttributeData Stamina_Data;
	UPROPERTY(ReplicatedUsing = OnRep_MaxStamina, EditAnywhere, Category = "Vital Attributes")
	FAttributeData MaxStamina_Data;

	UFUNCTION()
	void OnRep_Health();
	
	UFUNCTION()
	void OnRep_MaxHealth();

	UFUNCTION()
	void OnRep_Stamina();

	UFUNCTION()
	void OnRep_MaxStamina();

public:
	FORCEINLINE FAttributeData GetHealthData() const {return Health_Data;}
	FORCEINLINE FAttributeData GetMaxHealthData() const {return MaxHealth_Data;}
	FORCEINLINE FAttributeData GetStamina() const {return Stamina_Data;}
	FORCEINLINE FAttributeData GetMaxStamina() const {return MaxStamina_Data;}
};
