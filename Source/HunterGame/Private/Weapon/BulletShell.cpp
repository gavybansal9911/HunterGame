// Hunter Game by Gamer Guru.


#include "Weapon/BulletShell.h"

ABulletShell::ABulletShell()
{
	PrimaryActorTick.bCanEverTick = false;

	BulletShellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Shell Mesh"));
	SetRootComponent(BulletShellMesh);
}

void ABulletShell::BeginPlay()
{
	Super::BeginPlay();
}
