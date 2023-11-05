// Hunter Game by Gamer Guru.


#include "Character/HunterAnimInstance.h"
#include "Character/BaseCharacter.h"
#include "Component/CombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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
		Speed = HunterCharacter->GetCharacterMovement()->Velocity.Size();
		bIsFalling = HunterCharacter->GetCharacterMovement()->IsFalling();
		bIsCrouched = HunterCharacter->bIsCrouched;
		bIsAccelerating = HunterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
		
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

		if (HunterCharacter->Combat) {EquippedWeapon = HunterCharacter->Combat->GetWeaponInHand();}
		bIsCombatEnabled = HunterCharacter->IsCombatEnabled();
		if (EquippedWeapon) {EquippedWeaponName = EquippedWeapon->GetWeaponName();} else {EquippedWeaponName = EWeaponName::EWN_Max;}
		bIsAiming = HunterCharacter->IsAiming();
	}
}
