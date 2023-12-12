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
enum class EAIState : uint8
{
	EAIS_None = 0 UMETA(DisplayName = "None"),
	EAIS_Passive = 1 UMETA(DisplayName = "Passive"),
	EAIS_Investigating = 2 UMETA(DisplayName = "Investigating"),
	EAIS_Hunting = 3 UMETA(DisplayName = "Hunting"),
	EAIS_Chasing = 4 UMETA(DisplayName = "Chasing"),
	EAIS_Attacking = 5 UMETA(DisplayName = "Attacking"),
	EAIS_Retreating = 6 UMETA(DisplayName = "Retreating"),
	EAIS_RunningAway = 7 UMETA(DisplayName = "Running Away")
};

UENUM(BlueprintType)
enum class EAIAttackingState : uint8
{
	EAIAS_EyeToEyeCombat = 0 UMETA(DisplayName = "Eye To Eye Combat"),
	EAIAS_Assassinating = 1 UMETA(DisplayName = "Assassinating"),
	
	EAIAS_Max = 2 UMETA(DisplayName = "Max")
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
	EAIAS_Shooting UMETA(DisplayName = "Shooting"),
	
	EAIAS_Max UMETA(DisplayName = "Max")
};
