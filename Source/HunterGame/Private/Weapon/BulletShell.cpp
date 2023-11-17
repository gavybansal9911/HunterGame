// Hunter Game by Gamer Guru.


#include "Weapon/BulletShell.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ABulletShell::ABulletShell()
{
	PrimaryActorTick.bCanEverTick = false;

	BulletShellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Shell Mesh"));
	SetRootComponent(BulletShellMesh);
	BulletShellMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	BulletShellMesh->SetSimulatePhysics(true);
	BulletShellMesh->SetEnableGravity(true);
	BulletShellMesh->SetNotifyRigidBodyCollision(true);
}

void ABulletShell::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind OnHit to OnComponentHit delegate
	BulletShellMesh->OnComponentHit.AddDynamic(this, &ABulletShell::OnHit);

	// Add ejection force to bullet shell
	BulletShellMesh->AddImpulse(GetActorForwardVector() * ShellEjectionImpulse);
}

void ABulletShell::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (ShellSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ShellSound, GetActorLocation(), GetActorRotation(),
			1.f, 1.f, 0.f, nullptr, ShellSoundConcurrency);
	}
	
	// Set Destroy Timer
	GetWorldTimerManager().SetTimer(BulletDestroyHandle, this, &ABulletShell::DestroyBulletShell, BulletDestroyDelay, false);
}

void ABulletShell::DestroyBulletShell()
{
	Destroy();
	GetWorldTimerManager().ClearTimer(BulletDestroyHandle);
}
