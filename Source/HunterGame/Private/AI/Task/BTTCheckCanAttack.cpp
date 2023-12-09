// Hunter Game by Gamer Guru.


#include "AI/Task/BTTCheckCanAttack.h"
#include "AIController.h"
#include "AI/AIControllerBase.h"
#include "AI/EnemyBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Weapon/Weapon.h"

EBTNodeResult::Type UBTTCheckCanAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (AAIControllerBase* AIControllerBase = Cast<AAIControllerBase>(OwnerComp.GetAIOwner()))
    {
        if (AIControllerBase->GetAIEnemyCharacter()->GetOwnedWeapon() == nullptr) return EBTNodeResult::Succeeded;
        
        if (AActor* TargetActor = Cast<AActor>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject(BB_TargetActor_KeyName)))
        {
            const FVector DeltaLocation = AIControllerBase->GetAIEnemyCharacter()->GetActorLocation() - TargetActor->GetActorLocation();

            if (DeltaLocation.Size() <= AIControllerBase->GetAIEnemyCharacter()->GetOwnedWeapon()->GetWeaponRange())
            {
                AIControllerBase->SetStateAsAttacking(TargetActor);
                return EBTNodeResult::Succeeded;
            }
        }
    }

    return EBTNodeResult::Succeeded;
}
