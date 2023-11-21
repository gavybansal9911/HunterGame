// Hunter Game by Gamer Guru.


#include "AI/EnemyBase.h"
#include "AsyncTreeDifferences.h"
#include "AI/AIControllerBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Tasks/AITask_MoveTo.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Components/SphereComponent.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;

	MeleeAttackSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttachkSphere"));
	MeleeAttackSphere->SetupAttachment(GetMesh());
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	/** Binding Overlap CallBacks **/
	MeleeAttackSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnAttackSphereOverlap);
	MeleeAttackSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemyBase::OnAttackSphereEndOverlap);
	/** Binding Overlap CallBacks **/
	
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (PlayerCharacter)
	{
		EquippedWeaponType = EEquippedWeaponType::EEWT_Melee;
		GetInCombat(PlayerCharacter);
	}
}

void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!HasAuthority()) return;
	
	AIController = Cast<AAIControllerBase>(NewController);

	AIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	AIController->RunBehaviorTree(BehaviorTree);
}

void AEnemyBase::OnAttackSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GetWorldTimerManager().SetTimer(MeleeAttackTimerHandle, this, &AEnemyBase::MeleeAttackTimer, 2.f, true, 0.f);
}

void AEnemyBase::OnAttackSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GetWorldTimerManager().ClearTimer(MeleeAttackTimerHandle);
}

void AEnemyBase::GetInCombat(AActor* TargetActor)
{
	switch (EquippedWeaponType)
	{
	case EEquippedWeaponType::EEWT_Melee:
		GetInCombat_Melee(TargetActor);
		break;
	default:
		break;
	}
}

void AEnemyBase::GetInCombat_Melee(AActor* TargetActor)
{
	FAIMoveRequest AIMoveRequest;
	AIMoveRequest.SetGoalActor(TargetActor);
	AIController->MoveTo(AIMoveRequest);

	GetWorldTimerManager().SetTimer(MeleeCombatChaseTimerHandle, this, &AEnemyBase::MeleeCombatChaseTimer, 2.f, true, 0.f);
}

void AEnemyBase::Attack()
{
	switch (EquippedWeaponType)
	{
		case EEquippedWeaponType::EEWT_Melee:
			Attack_Melee();
			break;
		default:
			break;
	}
}

void AEnemyBase::Attack_Melee()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance) return;

	AnimInstance->Montage_Play(DaggerAttackMontage);
}

/** Timer CallBacks **/
void AEnemyBase::MeleeCombatChaseTimer()
{
	FAIMoveRequest AIMoveRequest;
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	AIMoveRequest.SetGoalActor(PlayerCharacter);
	AIController->MoveTo(AIMoveRequest);
}

void AEnemyBase::MeleeAttackTimer()
{
	Attack();
}
/** Timer CallBacks **/
