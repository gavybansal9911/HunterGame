// Hunter Game by Gamer Guru.


#include "Weapon/BulletShell.h"

ABulletShell::ABulletShell()
{
	PrimaryActorTick.bCanEverTick = false;

	BulletShellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Shell Mesh"));
	SetRootComponent(BulletShellMesh);
	BulletShellMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	BulletShellMesh->SetSimulatePhysics(true);
	BulletShellMesh->SetEnableGravity(true);
}

void ABulletShell::BeginPlay()
{
	Super::BeginPlay();
	BulletShellMesh->AddImpulse(GetActorForwardVector() * ShellEjectionImpulse);
}
