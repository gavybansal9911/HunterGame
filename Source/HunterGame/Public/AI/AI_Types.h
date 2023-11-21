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

UENUM(BlueprintType)
enum class EAISense : uint8
{
	EAIS_None UMETA(DisplayName = "None"),
	EAIS_Sight UMETA(DisplayName = "Sight"),
	EAIS_Hearing UMETA(DisplayName = "Hearing"),
	EAIS_Damage UMETA(DisplayName = "Damage")
};
