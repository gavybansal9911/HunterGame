// Hunter Game by Gamer Guru.


#include "Character/Animal/AnimalAnimInstance.h"
#include "Character/Animal/BaseAnimal.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAnimalAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// Owner Animal
	OwnerAnimalCharacter = Cast<ABaseAnimal>(TryGetPawnOwner());
}

void UAnimalAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwnerAnimalCharacter && OwnerAnimalCharacter->GetCharacterMovement())
	{
		/** Basic Movement **/
		FVector Local_Velocity = OwnerAnimalCharacter->GetVelocity();
		Local_Velocity.Z = 0;
		Speed = Local_Velocity.Size();
		
		bIsInAir = OwnerAnimalCharacter->GetCharacterMovement()->IsFalling();
		
		bIsAccelerating = OwnerAnimalCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
		/** Basic Movement **/
	}
}
