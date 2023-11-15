// Hunter Game by Gamer Guru.


#include "Character/HunterAnimInstance.h"
#include "Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapon/Weapon.h"

void UHunterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	HunterCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
}

void UHunterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (HunterCharacter && HunterCharacter->GetCharacterMovement())
	{
		/** Basic Movement **/
		Speed = HunterCharacter->GetCharacterMovement()->Velocity.Size();
		bIsFalling = HunterCharacter->GetCharacterMovement()->IsFalling();
		bIsCrouched = HunterCharacter->bIsCrouched;
		bIsAccelerating = HunterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
		/** Basic Movement **/
		
		/** Leaning **/
		CharacterRotationLastFrame = CharacterRotationThisFrame;
		CharacterRotationThisFrame = HunterCharacter->GetActorRotation();
		const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotationThisFrame, CharacterRotationLastFrame);
		const float Target = Delta.Yaw / DeltaSeconds;
		const float Interp = FMath::FInterpTo(Lean, Target, DeltaSeconds, 6.f);
		Lean = FMath::Clamp(Interp, -90.f, 90.f);
		/** Leaning **/

		/** Strafing **/
		// AimRotation is Global (Points according the world direction axis)
		const FRotator AimRotation = HunterCharacter->GetBaseAimRotation();
		// MovementRotation is local to the player (This function returns a FRotator in the direction of FVector passed in as a argument, In this case the HunterCharacter velocity)
		const FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(HunterCharacter->GetVelocity());
		const FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
		DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaSeconds, 6.f);
		YawOffset = DeltaRotation.Yaw;
		/** Strafing **/

		/** Combat **/
		EquippedWeapon = HunterCharacter->GetEquippedWeapon();
		bIsCombatEnabled = HunterCharacter->IsCombatEnabled();
		bIsAiming = HunterCharacter->IsAiming();
		AO_Yaw = HunterCharacter->GetAO_Yaw();       // Aim Yaw Offset
		AO_Pitch = HunterCharacter->GetAO_Pitch();   // Aim Pitch Offset
		if (bIsAiming && HunterCharacter->GetCameraBoom()->TargetArmLength != CAMERA_BOOM_AIM_TARGET_ARM_LENGTH)  // Not valid if TargetArmLength is already set correctly
		{
			const float NewTargetArmLength = HunterCharacter->GetCameraBoom()->TargetArmLength = FMath::FInterpTo(HunterCharacter->GetCameraBoom()->TargetArmLength, CAMERA_BOOM_AIM_TARGET_ARM_LENGTH, DeltaSeconds, 6.f);
			HunterCharacter->GetCameraBoom()->TargetArmLength = NewTargetArmLength;
		}
		else
		{
			if (HunterCharacter->GetCameraBoom()->TargetArmLength == CAMERA_BOOM_IDLE_TARGET_ARM_LENGTH) return;  // Return if TargetArmLength is already set correctly
			const float NewTargetArmLength = HunterCharacter->GetCameraBoom()->TargetArmLength = FMath::FInterpTo(HunterCharacter->GetCameraBoom()->TargetArmLength, CAMERA_BOOM_IDLE_TARGET_ARM_LENGTH, DeltaSeconds, 6.f);
			HunterCharacter->GetCameraBoom()->TargetArmLength = NewTargetArmLength;
		}
		/** Combat **/

		/** Inverse Kinematics **/
		if (bIsCombatEnabled && EquippedWeapon && EquippedWeapon->GetWeaponMesh() && HunterCharacter->GetMesh())
		{
			// Get the transform of the socket on the WeaponMesh named as LeftHandSocket (Socket Transform is adjusted in the Skeletal Mesh in the editor)
			LeftHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("LeftHandSocket"), ERelativeTransformSpace::RTS_World);

			/** Input Parameters for converting LeftHandTransform from WorldSpace to BoneSpace **/
			FVector OutPosition;   // Will be passed by reference.
			FRotator OutRotation;   // Will be passed by reference.
			/** Input Parameters for converting LeftHandTransform from WorldSpace to BoneSpace **/
			// Transforming the LeftHandTransform from WorldSpace to BoneSpace.
			// Here, "hand_r" is for a reference for the Transform. The LeftHandTransform will be relative to the Right Hand or "hand_r"
			HunterCharacter->GetMesh()->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(), FRotator::ZeroRotator, OutPosition, OutRotation);
			// Now, after Transforming to BoneSpace, OutPosition and OutRotation have valid data because they were passed by reference.
			LeftHandTransform.SetLocation(OutPosition);
			LeftHandTransform.SetRotation(FQuat(OutRotation));
		}
		/** Inverse Kinematics **/

		/** Turning in Place **/
		TurningInPlace = HunterCharacter->GetTurningInPlace();
		/** Turning in Place **/
	}
}
