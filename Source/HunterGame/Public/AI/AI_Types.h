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

UENUM(BlueprintType)
enum class EAIPerceptionSense : uint8
{
	EAIS_None UMETA(DisplayName = "None"),
	EAIS_Sight UMETA(DisplayName = "Sight"),
	EAIS_Hearing UMETA(DisplayName = "Hearing"),
	EAIS_Damage UMETA(DisplayName = "Damage")
};

UENUM(BlueprintType)
enum class EAIEnemyActionState : uint8
{
	EAIAS_None UMETA(DisplayName = "None"),
	EAIAS_TogglingWeapon UMETA(DisplayName = "Toggling Weapon"),
	
	EAIAS_Max UMETA(DisplayName = "Max")
};
