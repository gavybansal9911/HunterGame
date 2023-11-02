#pragma once

enum class EWeaponState : uint8
{
	EWS_Attached UMETA(DisplayName = "Attached"),
	EWS_Unattached UMETA(DisplayName = "Unattached"),

	EWS_Max UMETA(DisplayName = "Max")
};