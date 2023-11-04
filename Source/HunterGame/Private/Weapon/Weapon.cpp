// Hunter Game by Gamer Guru.


#include "Weapon/Weapon.h"
#include "Character/BaseCharacter.h"
#include "Component/CombatComponent.h"
#include "Component/InteractionComponent.h"
#include "Components/SphereComponent.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weaponmesh"));
	SetRootComponent(WeaponMesh);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Overlap);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECR_Ignore);

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Area Sphere"));
	AreaSphere->SetupAttachment(WeaponMesh);
	AreaSphere->SetGenerateOverlapEvents(true);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBeginOverlap);
	AreaSphere->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnEndOverlap);
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const ABaseCharacter* HunterCharacter = Cast<ABaseCharacter>(OtherActor))
	{
		if (HunterCharacter->InteractionComponent) {HunterCharacter->InteractionComponent->SetOverlappingActor(this);}
	}
}

void AWeapon::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (const ABaseCharacter* HunterCharacter = Cast<ABaseCharacter>(OtherActor))
	{
		if (HunterCharacter->InteractionComponent) {HunterCharacter->InteractionComponent->SetOverlappingActor(nullptr);}
	}
}

FString AWeapon::LookAt()
{
	FString Message = FString("Message");
	return Message;
}

void AWeapon::InteractWith(ABaseCharacter* HunterCharacter)
{
	Equip(HunterCharacter);
}

void AWeapon::Equip(const ABaseCharacter* HunterCharacter)
{
	if (WeaponState != EWeaponState::EWS_Unattached) return;

	if (AreaSphere->GetGenerateOverlapEvents()) {AreaSphere->SetGenerateOverlapEvents(false);}
	AttachToActor(HunterCharacter, InHandAttachSocketName);
	WeaponState = EWeaponState::EWS_Attached;
	AttachmentStatus = EAttachmentStatus::EAS_InHand;
	if (HunterCharacter->Combat) {HunterCharacter->Combat->SetWeaponInHand(this); HunterCharacter->Combat->SetIsCombatEnabled(true);}
}

void AWeapon::AttachToActor(const ACharacter* InParent, FName SocketName)
{
	const FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	AttachToComponent(InParent->GetMesh(), AttachmentTransformRules, SocketName);
}
