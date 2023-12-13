// Hunter Game by Gamer Guru.


#include "Character/Animal/AnimalAnimInstance.h"
#include "Character/Animal/BaseAnimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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

		/** IK **/
		// TODO: Find another approach to access to player character location
		if (ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{
			if (OwnerAnimalCharacter->GetActorLocation().Size() -
				PlayerCharacter->GetActorLocation().Size() < MinDoIKRange)
					{if (bIsInAir == false)
						{bShouldDoIK = true;}} else {bShouldDoIK = false;}
		} else {bShouldDoIK = false;}
		/** IK **/
	}
}
