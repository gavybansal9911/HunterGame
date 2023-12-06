#pragma once

UENUM(BlueprintType)
enum class EAIMovementMode : uint8
{
	EMM_None UMETA(DisplayName = "None"),
	EMM_Idle UMETA(DisplayName = "Idle"),
	EMM_Walking UMETA(DisplayName = "Walking"),
	EMM_Jogging UMETA(DisplayName = "Jogging"),
	EMM_Running UMETA(DisplayName = "Running")
};

UENUM(BlueprintType)
enum class EEquippedWeaponType : uint8
{
	EEWT_None UMETA(DisplayName = "None"),
	EEWT_Melee UMETA(DisplayName = "Melee"),
	EEWT_Ranged UMETA(DisplayName = "Ranged"),
	EEWT_Both UMETA(DisplayName = "Both")
};

UENUM(Blueprintable)
enum class EAIState : uint8
{
	EAIS_None UMETA(DisplayName = "None"),
	EAIS_Passive UMETA(DisplayName = "Passive"),
	EAIS_Hunting UMETA(DisplayName = "Hunting"),
	EAIS_Chasing UMETA(DisplayName = "Chasing"),
	EAIS_Attacking UMETA(DisplayName = "Attacking"),
	EAIS_Retreating UMETA(DisplayName = "Retreating"),
	EAIS_Investigating UMETA(DisplayName = "Investigating")
};

// Use ScriptName metadata to provide a unique name for the enum in Python
UENUM(BlueprintType)
enum class EAIPerceptionSense : uint8
{
	EAIS_None UMETA(DisplayName = "None"),
	EAIS_Sight UMETA(DisplayName = "Sight"),
	EAIS_Hearing UMETA(DisplayName = "Hearing"),
	EAIS_Damage UMETA(DisplayName = "Damage")
};
