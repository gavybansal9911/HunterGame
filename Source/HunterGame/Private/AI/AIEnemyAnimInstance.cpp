// Hunter Game by Gamer Guru.


#include "AI/AIEnemyAnimInstance.h"
#include "AI/EnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"
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
		/** Basic Movement **/

		/** Combat **/
		EquippedWeapon = OwnerAIEnemyCharacter->GetOwnedWeapon();
		bHaveWeapon = OwnerAIEnemyCharacter->GetOwnedWeapon() ? true : false;
		EquippedWeaponType = EquippedWeapon ? EquippedWeapon->GetWeaponType() : EWeaponType::EWC_Max;
		EquippedWeaponName = EquippedWeapon ? EquippedWeapon->GetWeaponName() : EWeaponName::EWN_Max;
		/** Combat **/
	}
}
