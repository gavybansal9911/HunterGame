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
