// Hunter Game by Gamer Guru.


#include "AI/AIEnemyAnimInstance.h"
#include "AI/EnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapon/Weapon.h"

void UAIEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerAIEnemyCharacter = Cast<AEnemyBase>(TryGetPawnOwner());
}

void UAIEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwnerAIEnemyCharacter && OwnerAIEnemyCharacter->GetCharacterMovement())
	{
		/** Basic Movement **/
		FVector Local_Velocity = OwnerAIEnemyCharacter->GetVelocity();
		Local_Velocity.Z = 0;
		Speed = Local_Velocity.Size();
		
		bIsInAir = OwnerAIEnemyCharacter->GetCharacterMovement()->IsFalling();
		
		bIsAccelerating = OwnerAIEnemyCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;

		// Leaning
		CharacterRotationLastFrame = CharacterRotationThisFrame;
		CharacterRotationThisFrame = OwnerAIEnemyCharacter->GetActorRotation();
		const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotationThisFrame, CharacterRotationLastFrame);
		const float Target = Delta.Yaw / DeltaSeconds;
		const float Interp = FMath::FInterpTo(Lean, Target, DeltaSeconds, 6.f);
		Lean = FMath::Clamp(Interp, -90.f, 90.f);

		// Strafing
		// AimRotation is Global (Points according the world direction axis)
		const FRotator AimRotation = OwnerAIEnemyCharacter->GetBaseAimRotation();
		// MovementRotation is local to the character (This function returns a FRotator in the direction of FVector passed in as a argument, In this case the HunterCharacter velocity)
		const FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(OwnerAIEnemyCharacter->GetVelocity());
		const FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
		DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaSeconds, 30.f);   // Play with the InterpSpeed if the blending is too wacky ot too slow.
		YawOffset = DeltaRotation.Yaw;
		/** Basic Movement **/

		
		/** Combat **/
		EquippedWeapon = OwnerAIEnemyCharacter->GetOwnedWeapon();

		// Have any weapon (in or our hand)
		bHaveWeapon = OwnerAIEnemyCharacter->GetOwnedWeapon() ? true : false;

		// Equipped weapon is in hand ?
		bWeaponIsInHand = OwnerAIEnemyCharacter->GetOwnedWeapon() &&
			OwnerAIEnemyCharacter->GetOwnedWeapon()->GetWeaponAttachmentStatus() == EAttachmentStatus::EAS_InHand ? true : false;

		EquippedWeaponType = EquippedWeapon ? EquippedWeapon->GetWeaponType() : EWeaponType::EWC_Max;
		EquippedWeaponName = EquippedWeapon ? EquippedWeapon->GetWeaponName() : EWeaponName::EWN_Max;

		bIsAiming = OwnerAIEnemyCharacter->IsAiming();

		if (OwnerAIEnemyCharacter->GetEnemyState() == EAIState::EAIS_Attacking ||
			OwnerAIEnemyCharacter->GetEnemyState() == EAIState::EAIS_Retreating ||
			OwnerAIEnemyCharacter->GetEnemyState() == EAIState::EAIS_Hunting)
		{
			// Fix right hand rotation
			FTransform RightHandTransform = OwnerAIEnemyCharacter->GetMesh()->GetSocketTransform(FName("hand_r"), RTS_World);
			FRotator Local_RightHandRotation = UKismetMathLibrary::FindLookAtRotation(RightHandTransform.GetLocation(), RightHandTransform.GetLocation() + (RightHandTransform.GetLocation() - OwnerAIEnemyCharacter->GetHitTarget()));
			RightHandRotationOverride = FMath::RInterpTo(RightHandRotationOverride, Local_RightHandRotation, DeltaSeconds, 15.f);

			/** Debug **/
			if (EquippedWeapon)
			{
				FTransform MuzzleTipTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("MuzzleFlash"));
				FVector MuzzleX(FRotationMatrix(MuzzleTipTransform.GetRotation().Rotator()).GetUnitAxis(EAxis::X));
				DrawDebugLine(GetWorld(), MuzzleTipTransform.GetLocation(), MuzzleTipTransform.GetLocation() + MuzzleX * 1000.f, FColor::Yellow);
				DrawDebugLine(GetWorld(), MuzzleTipTransform.GetLocation(), OwnerAIEnemyCharacter->GetHitTarget(), FColor::Red);
				/** Debug **/
			}
			
			// FABRIK   (Apply only if the hit target is close enough to see the enemy clearly)
			bApplyFABRIK = OwnerAIEnemyCharacter->GetActorLocation().Size() -
				OwnerAIEnemyCharacter->GetHitTarget().Size() > 500.f ? false : true;  // Here, 500 is the range in which FABRIK should be applied.
				// Try to keep this range small for better performance
			if (bApplyFABRIK && EquippedWeapon)
			{
				// Get the transform of the socket on the WeaponMesh named as LeftHandSocket (Socket Transform is adjusted in the Skeletal Mesh in the editor)
				LeftHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("LeftHandSocket"), RTS_World);
				
				/** Input Parameters for converting LeftHandTransform from WorldSpace to BoneSpace **/
				FVector OutPosition;   // Will be passed by reference.
				FRotator OutRotation;   // Will be passed by reference.
				/** Input Parameters for converting LeftHandTransform from WorldSpace to BoneSpace **/
				// Transforming the LeftHandTransform from WorldSpace to BoneSpace.
				// Here, "hand_r" is for a reference for the Transform. The LeftHandTransform will be relative to the Right Hand or "hand_r"
				OwnerAIEnemyCharacter->GetMesh()->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(), FRotator::ZeroRotator, OutPosition, OutRotation);
				// Now, after Transforming to BoneSpace, OutPosition and OutRotation have valid data because they were passed by reference.
				LeftHandTransform.SetLocation(OutPosition);
				LeftHandTransform.SetRotation(FQuat(OutRotation));
			}
		}
		/** Combat **/
	}
}
