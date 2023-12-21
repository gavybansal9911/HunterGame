// Hunter Game by Gamer Guru.


#include "AI/Task/BTTGetLocAroundLeader_Animal.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/AnimalFollowerInterface.h"

EBTNodeResult::Type UBTTGetLocAroundLeader_Animal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent())
	{
		if (OwnerComp.GetAIOwner()->GetPawn()->ActorHasTag("Follower"))
		{
			if (IAnimalFollowerInterface* AnimalFollower = Cast<IAnimalFollowerInterface>(OwnerComp.GetAIOwner()->GetPawn()))
			{
				FVector Origin;
				if (AnimalFollower->GetLeaderActor())
					{Origin = AnimalFollower->GetLeaderActor()->GetActorLocation();}
				else
					{Origin = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();}
				FVector Local_PointOfInterest;
				UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(GetWorld(), Origin,
					Local_PointOfInterest, NavigableAreaRadius);

				Local_PointOfInterest.Z = AnimalFollower->GetLeaderActor()->GetActorLocation().Z;

				BlackboardComponent->SetValueAsVector(BB_PointOfInterest_KeyName, Local_PointOfInterest);

				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}
