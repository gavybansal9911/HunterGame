// Hunter Game by Gamer Guru.


#include "Weapon/Projectile.h"
#include "Components/BoxComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	SetRootComponent(CollisionBox);
	CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);   // Is Dynamic
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);   // Make sure it generate hit events.
	CollisionBox->SetCollisionResponseToChannels(ECollisionResponse::ECR_Ignore);  // Make sure it doesn't collide.
	/** Enable collision for particular channels **/
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	/** Enable collision for particular channels **/
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

