// Hunter Game by Gamer Guru.


#include "AI/Task/BTTSetCharacterMaxWalkSpeed.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UBTTSetCharacterMaxWalkSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (OwnerComp.GetAIOwner() == nullptr || OwnerComp.GetAIOwner()->GetPawn() == nullptr) return EBTNodeResult::Failed;
	
	if (ACharacter* Character = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		if (Character->GetCharacterMovement())
		{
			Character->GetCharacterMovement()->MaxWalkSpeed = NewMaxWalkSpeed;
			return EBTNodeResult::Succeeded;
		}
	}
	
	return EBTNodeResult::Failed;
}
