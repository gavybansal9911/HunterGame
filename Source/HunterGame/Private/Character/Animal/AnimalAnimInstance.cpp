// Hunter Game by Gamer Guru.


#include "Character/Animal/AnimalAnimInstance.h"
#include "KismetAnimationLibrary.h"
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
		/** General **/
		// TODO: Find another approach to access to player character location
		if (const ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{
			DistanceToPlayer = OwnerAnimalCharacter->GetActorLocation().Size() -
				PlayerCharacter->GetActorLocation().Size();
			DistanceToPlayer = FMath::Abs(DistanceToPlayer);

			GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("%f"), DistanceToPlayer));
		}
		/** General **/
		
		/** Movement **/
		Velocity = OwnerAnimalCharacter->GetVelocity();
		Velocity_XY = Velocity;
		Velocity_XY.Z = 0;
		
		Speed = Velocity_XY.Size();
		
		bIsInAir = OwnerAnimalCharacter->GetCharacterMovement()->IsFalling();
		
		bIsAccelerating = OwnerAnimalCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
		
		YawOffset = UKismetAnimationLibrary::CalculateDirection(OwnerAnimalCharacter->GetVelocity(), OwnerAnimalCharacter->GetActorRotation());
		FRotator NewRotation = OwnerAnimalCharacter->GetActorRotation();
		NewRotation.Yaw = FMath::FInterpTo(NewRotation.Yaw, NewRotation.Yaw + YawOffset, DeltaSeconds, RotationInterpSpeed);
		OwnerAnimalCharacter->SetActorRotation(NewRotation);

		if (DistanceToPlayer < 20000.f)
		{
			// Turning
			const FVector AnimalForwardVector = OwnerAnimalCharacter->GetActorForwardVector();
			const FVector VelocityDirectionVector = Velocity_XY.GetSafeNormal();
			if (!AnimalForwardVector.IsNearlyZero() && !VelocityDirectionVector.IsNearlyZero())
			{
				const float CosineTheta = FVector::DotProduct(AnimalForwardVector.GetSafeNormal(), VelocityDirectionVector.GetSafeNormal());
				const float ThetaRadians = FMath::Acos(FMath::Clamp(CosineTheta, -1.0f, 1.0f));

				// Use cross product to determine rotation direction
				const FVector CrossProduct = FVector::CrossProduct(AnimalForwardVector, VelocityDirectionVector);
				const float RotationDirection = FMath::Sign(CrossProduct.Z);
				const float RotationDirection_Inverse = -RotationDirection;
			
				// ThetaRadians now contains the angle between VectorA and VectorB in radians
				const float ThetaDegrees = FMath::RadiansToDegrees(ThetaRadians) * RotationDirection_Inverse;
				// ThetaDegrees now contains the angle in degrees
				//float MappedAngle = FMath::UnwindDegrees(ThetaDegrees);
				Turn = ThetaDegrees;
			}
			else
			{
				Turn = 0.f;
			}
		} else {Turn = 0.f;}
		/** Movement **/

		/** IK **/
		if (DistanceToPlayer < MinDoIKRange && bIsInAir == false)
			{bShouldDoIK = true;} else {bShouldDoIK = false;}
		/** IK **/
	}
}
