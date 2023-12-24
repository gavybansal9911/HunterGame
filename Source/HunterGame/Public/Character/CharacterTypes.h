#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Unequipped UMETA(DisplayName = "Unequipped"),
	ECS_Equipped UMETA(DisplayName = "Equipped"),
	ECS_Dead UMETA(DisplayName = "Dead"),
	
	ECS_Max UMETA(DisplayName = "Max")
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	EAS_Idle UMETA(DisplayName = "Idle"),
	EAS_Crouched UMETA(DisplayName = "Crouched"),
	
	EAS_Max UMETA(DisplayName = "Max")	
};

UENUM(BlueprintType)
enum class ECharacterMovementState : uint8
{
	ECMS_Walking = 0 UMETA(DisplayName = "Walking"),
	ECMS_Running = 1 UMETA(DisplayName = "Walking"),
	ECMS_Sprinting = 2 UMETA(DisplayName = "Sprinting"),
	
	ECMS_Max = 9 UMETA(DisplayName = "Max")
};

UENUM(BlueprintType)
enum class ETurningInPlace : uint8
{
	ETIP_Left UMETA(DisplayName = "Turning Left"),
	ETIP_Right UMETA(DisplayName = "Turning Right"),
	ETIP_NotTurning UMETA(DisplayName = "Not Turning"),
	
	ETIP_Max UMETA(DisplayName = "Max")
};

UENUM(BlueprintType)
enum class ECameraMode : uint8
{
	ECM_ThirdPerson UMETA(DisplayName = "Third Person"),
	ECM_SemiFirstPerson UMETA(DisplayName = "Semi-First Person"),
	ECM_FirstPerson UMETA(DisplayName = "First Person"),
	
	ECM_Max UMETA(DisplayName = "Max")
};