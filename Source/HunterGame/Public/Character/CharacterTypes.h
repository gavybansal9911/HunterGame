#pragma once

enum class ECharacterState : uint8
{
	ECS_Unequipped UMETA(DisplayName = "Unequipped"),
	ECS_Equipped UMETA(DisplayName = "Equipped"),
	
	ECS_Max UMETA(DisplayName = "Max")
};

enum class EActionState : uint8
{
	EAS_Idle UMETA(DisplayName = "Idle"),
	EAS_Crouched UMETA(DisplayName = "Crouched"),
	
	EAS_Max UMETA(DisplayName = "Max")	
};