#pragma once

UENUM(BlueprintType)
enum class EAnimalName : uint8
{
	EAN_Zebra = 0 UMETA(DisplayName = "Zebra"),
	EAN_Elephant = 0 UMETA(DisplayName = "Elephant"),
	EAN_WhiteRhino = 1 UMETA(DisplayName = "White Rhino"),
	EAN_Lion = 2 UMETA(DisplayName = "Lion"),
	EAN_Tiger = 2 UMETA(DisplayName = "Tiger"),
	
	EAN_Max = 99 UMETA(DisplayName = "Max")
};

UENUM(BlueprintType)
enum class EAnimalModeOfFeeding : uint8
{
	EAMF_Herbivore = 0 UMETA(DisplayName = "Herbivore"),
	EAMF_Omnivore = 1 UMETA(DisplayName = "Omnivore"),
	EAMF_Carnivore = 0 UMETA(DisplayName = "Carnivore"),
	
	EAMF_Max = 3 UMETA(DisplayName = "Max")
};

UENUM(BlueprintType)
enum class EAgeStatus : uint8
{
	EAS_NewBorn = 0 UMETA(DisplayName = "New Born"),
	EAS_Kid = 1 UMETA(DisplayName = "Kid"),
	EAS_Adult = 2 UMETA(DisplayName = "Adult"),
	
	EAS_Max = 3 UMETA(DisplayName = "Max")
};

UENUM(BlueprintType)
enum class EAnimalState : uint8
{
	EAS_Passive = 0 UMETA(DisplayName = "Passive"),
	EAS_LookingForFood = 1 UMETA(DisplayName = "Looking For Food"),
	EAS_Hunting = 2 UMETA(DisplayName = "Hunting"),  // 2 further possibilities (have found prey and is looking for prey)
	EAS_Chasing = 3 UMETA(DisplayName = "Chasing"),
	EAS_Attacking = 4 UMETA(DisplayName = "Attacking"),
	EAS_IsUnderAttack = 5 UMETA(DisplayName = "Is Under Attack"),
	EAS_RunningAway = 6 UMETA(DisplayName = "Running Away"),
	EAS_Dead = 7 UMETA(DisplayName = "Dead"),
	
	EAS_Max = 8 UMETA(DisplayName = "Max")
};

UENUM(BlueprintType)
enum class EAnimalActionState : uint8
{
	EAAS_Idle = 0 UMETA(DisplayName = "Idle"),
	
	EAAS_Max = 1 UMETA(DisplayName = "Max")
};


// TODO: Enum for animal mood (animal mood will be calculated based on the behavior factors defined in the animal survival component)

// TODO: Enum for family systems like wolfs lives in packs, lions make prides, elephants lives in groups
