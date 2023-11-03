#pragma once

UENUM(BlueprintType)
enum class EWeaponClass : uint8
{
	EWC_Primary UMETA(DisplayName = "Primary"),
	EWC_Secondary UMETA(DisplayName = "Secondary"),
	
	EWC_Max UMETA(DisplayName = "Max")
};

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	EWS_Attached UMETA(DisplayName = "Attached"),
	EWS_Unattached UMETA(DisplayName = "Unattached"),

	EWS_Max UMETA(DisplayName = "Max")
};

UENUM(BlueprintType)
enum class EAttachmentStatus : uint8
{
	EAS_InHand UMETA(DisplayName = "InHand"),
	EAS_OutHand UMETA(DisplayName = "OutHand"),
	
	EAS_Max UMETA(DisplayName = "Max")
};

UENUM(BlueprintType)
enum class EWeaponName : uint8
{
	EWN_Revolver UMETA(DisplayName = "Revolver"),
	EWN_Rifle UMETA(DisplayName = "Rifle"),

	EWN_Max UMETA(DisplayName = "Max")
};