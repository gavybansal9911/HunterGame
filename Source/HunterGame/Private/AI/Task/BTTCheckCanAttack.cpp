// Hunter Game by Gamer Guru.


#include "AI/Task/BTTCheckCanAttack.h"

#include "AIController.h"

EBTNodeResult::Type UBTTCheckCanAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (AAIController* OwnerAIController = Cast<AAIController>(OwnerComp.GetAIOwner()))
    {
        OwnerAIController->GetPawn();
    }

    return Super::ExecuteTask(OwnerComp, NodeMemory);
}
