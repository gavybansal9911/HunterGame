// Hunter Game by Gamer Guru.


#include "Component/AIEnemy/AIEnemyCombatComponent.h"
#include "AI/EnemyBase.h"
#include "Weapon/Weapon.h"
#include "Weapon/WeaponTypes.h"

UAIEnemyCombatComponent::UAIEnemyCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAIEnemyCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAIEnemyCombatComponent::PlayAnimationMontage(UAnimMontage* AnimMontage, FName SectionName, bool bJumpToSection)
{
	if (OwnerAIEnemy == nullptr || OwnerAIEnemy->GetMesh() == nullptr || AnimMontage == nullptr) return;
	
	if (UAnimInstance* AnimInstance = OwnerAIEnemy->GetMesh()->GetAnimInstance())
	{
		AnimInstance->Montage_Play(AnimMontage);

		if (bJumpToSection)
		{
			AnimInstance->Montage_JumpToSection(SectionName, AnimMontage);
		}
	}
}

void UAIEnemyCombatComponent::Init_Weapon()
{
	if (OwnerAIEnemy == nullptr) return;
	if (GetWorld() == nullptr) return;
	
	if (WeaponClass)
	{
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Owner = OwnerAIEnemy;
		ActorSpawnParameters.Instigator = OwnerAIEnemy;
		//AActor* Weapon_Actor = GetWorld()->SpawnActor(WeaponClass, OwnerAIEnemy->GetActorTransform(), ActorSpawnParameters);
		AActor* Weapon_Actor = GetWorld()->SpawnActor(WeaponClass);

		Weapon = Cast<AWeapon>(Weapon_Actor);
		if (Weapon)
		{
			Weapon->SetOwner(OwnerAIEnemy);
			FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget,
				EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
			Weapon->AttachToComponent(OwnerAIEnemy->GetMesh(), AttachmentTransformRules, Weapon->GetOutHandAttachSocketName());
			Weapon->SetWeaponAttachmentStatus(EAttachmentStatus::EAS_OutHand);
			Weapon->SetWeaponState(EWeaponState::EWS_Attached);
		}
	}
}

void UAIEnemyCombatComponent::ToggleWeapon()
{
	if (OwnerAIEnemy == nullptr) return;
	if (OwnerAIEnemy->GetEnemyActionState() != EAIEnemyActionState::EAIAS_None) return;
	PlayToggleWeaponAnimMontage();
	OwnerAIEnemy->SetEnemyActionState(EAIEnemyActionState::EAIAS_TogglingWeapon);
}

void UAIEnemyCombatComponent::PlayToggleWeaponAnimMontage()
{
	if (Weapon == nullptr || OwnerAIEnemy == nullptr || OwnerAIEnemy->GetMesh() == nullptr) return;

	if (UAnimInstance* AnimInstance = OwnerAIEnemy->GetMesh()->GetAnimInstance())
	{
		switch (Weapon->GetWeaponAttachmentStatus())
		{
			case EAttachmentStatus::EAS_OutHand:
				AnimInstance->Montage_Play(Weapon->TakeOutWeaponMontage);
				break;
			case EAttachmentStatus::EAS_InHand:
				AnimInstance->Montage_Play(Weapon->PutWeaponInMontage);
				break;
			default:
				break;
		}
	}
}

void UAIEnemyCombatComponent::ToggleWeaponAnimNotifyCallBack()
{
	if (!Weapon) return;

	if (OwnerAIEnemy) {OwnerAIEnemy->SetEnemyActionState(EAIEnemyActionState::EAIAS_None);}
	
	if (Weapon->GetWeaponAttachmentStatus() == EAttachmentStatus::EAS_OutHand)
	{
		EnableCombat();
		return;
	}
	if (Weapon->GetWeaponAttachmentStatus() == EAttachmentStatus::EAS_InHand)
	{
		DisableCombat();
		return;
	}
}

void UAIEnemyCombatComponent::EnableCombat()
{
	if (!Weapon) return;
	
	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(OwnerAIEnemy->GetMesh(), AttachmentTransformRules, Weapon->GetInHandAttachSocketName());
	Weapon->SetWeaponAttachmentStatus(EAttachmentStatus::EAS_InHand);
	UpdateAttackRadius();
}

void UAIEnemyCombatComponent::DisableCombat()
{
	if (!Weapon) return;

	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(OwnerAIEnemy->GetMesh(), AttachmentTransformRules, Weapon->GetOutHandAttachSocketName());
	Weapon->SetWeaponAttachmentStatus(EAttachmentStatus::EAS_OutHand);
}

void UAIEnemyCombatComponent::UpdateAttackRadius()
{
	if (OwnerAIEnemy)
	{
		OwnerAIEnemy->UpdateAttackRadius();
	}
}

void UAIEnemyCombatComponent::Aim()
{
	bIsAiming = true;
}

void UAIEnemyCombatComponent::UnAim()
{
	bIsAiming = false;
}

void UAIEnemyCombatComponent::Attack()
{
	if (OwnerAIEnemy == nullptr || Weapon == nullptr) return;

	Aim();
	const FName SectionName = bIsAiming ? FName("Aim") : FName("Hip");
	PlayAnimationMontage(Weapon->WeaponShootMontage, SectionName, true);
	FTransform MuzzleTipTransform = Weapon->GetWeaponMesh()->GetSocketTransform(FName("MuzzleFlash"));
	FVector MuzzleX(FRotationMatrix(MuzzleTipTransform.GetRotation().Rotator()).GetUnitAxis(EAxis::X));
	FVector HitTarget = MuzzleTipTransform.GetLocation() + (MuzzleX * 1000.f);
	Weapon->Shoot(HitTarget);
	OwnerAIEnemy->SetEnemyActionState(EAIEnemyActionState::EAIAS_Shooting);
}

void UAIEnemyCombatComponent::OnAIStateSetAsRunningAway()
{
	UnAim();
}
