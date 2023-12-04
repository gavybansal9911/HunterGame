// Hunter Game by Gamer Guru.


#include "Weapon/Weapon.h"
#include "Character/BaseCharacter.h"
#include "Component/CombatComponent.h"
#include "Component/InteractionComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Net/UnrealNetwork.h"
#include "PlayerController/HunterPlayerController.h"
#include "Weapon/BulletShell.h"

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

void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeapon, WeaponState);
	DOREPLIFETIME(AWeapon, Ammo);
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
	if (const ABaseCharacter* PlayerCharacter = Cast<ABaseCharacter>(OtherActor))
	{
		if (PlayerCharacter->IsLocallyControlled() && WeaponState == EWeaponState::EWS_Unattached) {HighlightWeapon();}
		if (PlayerCharacter->InteractionComponent)
			{PlayerCharacter->InteractionComponent->SetOverlappingActor(this);}
	}
}

void AWeapon::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UnHighlightWeapon();
	
	if (const ABaseCharacter* PlayerCharacter = Cast<ABaseCharacter>(OtherActor))
	{
		if (PlayerCharacter->IsLocallyControlled() && WeaponState == EWeaponState::EWS_Unattached) {UnHighlightWeapon();}
		if (PlayerCharacter->InteractionComponent)
			{PlayerCharacter->InteractionComponent->SetOverlappingActor(nullptr);}
	}
}

void AWeapon::HighlightWeapon()
{
	WeaponMesh->SetRenderCustomDepth(true);
	WeaponMesh->SetCustomDepthStencilValue(500);
}

void AWeapon::UnHighlightWeapon()
{
	WeaponMesh->SetRenderCustomDepth(false);
	WeaponMesh->SetCustomDepthStencilValue(0);
}

FString AWeapon::LookAt()
{
	FString Message = FString("Message");
	return Message;
}

void AWeapon::InteractWith(ABaseCharacter* PlayerCharacter)
{
	if (!PlayerCharacter->CombatComponent) return;
	PlayerCharacter->CombatComponent->EquipWeapon(this);
}

void AWeapon::Shoot(const FVector& HitTarget)
{
	if (FireAnimationAsset)
	{
		GetWeaponMesh()->PlayAnimation(FireAnimationAsset, false);   // Play Weapon Animation
	}
	if (BulletShellClass)
	{
		const USkeletalMeshSocket* AmmoEjectSocket = WeaponMesh->GetSocketByName(FName("AmmoEject"));
		if (AmmoEjectSocket)
		{
			FTransform SocketTransform = AmmoEjectSocket->GetSocketTransform(WeaponMesh);
			if (GetWorld())
			{
				FRotator RandomOffsetRotator = FRotator(FMath::RandRange(0, 45), FMath::RandRange(0, 45), FMath::RandRange(0, 45));
				FRotator BulletShellSpawnRotation = SocketTransform.GetRotation().Rotator() + RandomOffsetRotator;
				GetWorld()->SpawnActor<ABulletShell>(BulletShellClass, SocketTransform.GetLocation(), BulletShellSpawnRotation);
			}
		}
	}
	SpendRound();
}

void AWeapon::AddAmmoToWeapon(int32 AmmoToAdd)
{
	Ammo = FMath::Clamp(Ammo + AmmoToAdd, 0, MagazineSize);
	SetHUDWeaponAmmo();
}

void AWeapon::SetHUDWeaponAmmo()
{
	OwnerCharacter = OwnerCharacter == nullptr ? Cast<ABaseCharacter>(GetOwner()) : OwnerCharacter;
	if (OwnerCharacter)
	{
		OwnerController = OwnerController == nullptr ? Cast<AHunterPlayerController>(OwnerCharacter->GetController()) : OwnerController;
		if (OwnerController)
		{
			OwnerController->SetHUDWeaponAmmo(Ammo, GetAmmoInInventory());
		}
	}
}

int32 AWeapon::GetAmmoInInventory()
{
	if (!OwnerCharacter) return 0;
	return OwnerCharacter->GetAmmoInInventory();
}

void AWeapon::SpendRound()
{
	Ammo = FMath::Clamp(Ammo - 1, 0, MagazineSize);
	SetHUDWeaponAmmo();
}

bool AWeapon::IsMagazineEmpty() const
{
	return Ammo <= 0;
}

/** Rep Notifies **/
void AWeapon::OnRep_Ammo()
{
	SetHUDWeaponAmmo();
}

void AWeapon::OnRep_Owner()
{
	Super::OnRep_Owner();
	
	if (Owner == nullptr)
	{
		OwnerCharacter = nullptr;
		OwnerController = nullptr;
	}
	else
	{
		SetHUDWeaponAmmo();
	}
}
/** Rep Notifies **/
