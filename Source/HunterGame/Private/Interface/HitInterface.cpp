// Hunter Game by Gamer Guru.


#include "Interface/HitInterface.h"
#include "GameFramework/Character.h"


void IHitInterface::GetHit(FName HitBoneName, FVector HitBoneLocation)
{
}

void IHitInterface::PlayHitReactMontage(ACharacter* HitCharacter, UAnimMontage* Montage, FName SectionName)
{
	if (UAnimInstance* AnimInstance = HitCharacter->GetMesh()->GetAnimInstance())
	{
		AnimInstance->Montage_Play(Montage);
		AnimInstance->Montage_JumpToSection(SectionName);
	}
}

USkinnedMeshComponent* IHitInterface::GetCharacterMesh()
{
	return nullptr;
}
