#pragma once

enum class EWeaponState : uint8
{
	EWS_Attached UMETA(DisplayName = "Attached"),
	EWS_Unattached UMETA(DisplayName = "Unattached"),

	EWS_Max UMETA(DisplayName = "Max")
};

enum class EAttachmentStatus : uint8
{
	EAS_InHand UMETA(DisplayName = "InHand"),
	EAS_OutHand UMETA(DisplayName = "OutHand"),
	
	EAS_Max UMETA(DisplayName = "Max")
};