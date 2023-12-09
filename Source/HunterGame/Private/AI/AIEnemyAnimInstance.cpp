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
		DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaSeconds, 6.f);
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
		/** Combat **/
	}
}
