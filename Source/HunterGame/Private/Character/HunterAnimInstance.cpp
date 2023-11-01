// Hunter Game by Gamer Guru.


#include "Character/HunterAnimInstance.h"

#include "Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

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
		IsFalling = HunterCharacter->GetCharacterMovement()->IsFalling();
	}
}
