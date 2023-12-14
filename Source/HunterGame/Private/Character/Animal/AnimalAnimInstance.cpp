// Hunter Game by Gamer Guru.


#include "Character/Animal/AnimalAnimInstance.h"
#include "Character/Animal/BaseAnimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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
		/** Movement **/
		FVector Local_Velocity = OwnerAnimalCharacter->GetVelocity();
		Local_Velocity.Z = 0;
		Speed = Local_Velocity.Size();
		
		bIsInAir = OwnerAnimalCharacter->GetCharacterMovement()->IsFalling();
		
		bIsAccelerating = OwnerAnimalCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;

		// Animal rotation
		YawOffset = CalculateDirection(OwnerAnimalCharacter->GetVelocity(), OwnerAnimalCharacter->GetActorRotation());
		FRotator NewRotation = OwnerAnimalCharacter->GetActorRotation();
		NewRotation.Yaw = FMath::FInterpTo(NewRotation.Yaw, NewRotation.Yaw + YawOffset, DeltaSeconds, 2.f);
		OwnerAnimalCharacter->SetActorRotation(NewRotation);
		/** Movement **/

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
