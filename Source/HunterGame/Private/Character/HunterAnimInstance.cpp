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
		
		/** Leaning **/
		CharacterRotationLastFrame = CharacterRotationThisFrame;
		CharacterRotationThisFrame = HunterCharacter->GetActorRotation();
		const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotationThisFrame, CharacterRotationLastFrame);
		const float Target = Delta.Yaw / DeltaSeconds;
		const float Interp = FMath::FInterpTo(Lean, Target, DeltaSeconds, 6.f);
		Lean = FMath::Clamp(Interp, -90.f, 90.f);
		/** Leaning **/

		if (HunterCharacter->Combat) {EquippedWeapon = HunterCharacter->Combat->GetWeaponInHand();}
		bIsCombatEnabled = HunterCharacter->IsCombatEnabled();
		if (EquippedWeapon) {EquippedWeaponName = EquippedWeapon->GetWeaponName();} else {EquippedWeaponName = EWeaponName::EWN_Max;}
		bIsAiming = HunterCharacter->IsAiming();
	}
}
