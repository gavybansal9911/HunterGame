// Hunter Game by Gamer Guru.


#include "Actor/BaseItemActor.h"
#include "Character/BaseCharacter.h"
#include "Components/SphereComponent.h"

ABaseItemActor::ABaseItemActor()
{
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	SetRootComponent(ItemMesh);
	ItemMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Area Sphere"));
	AreaSphere->SetupAttachment(ItemMesh);
}

void ABaseItemActor::BeginPlay()
{
	Super::BeginPlay();

	AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseItemActor::OnOverlap);
	AreaSphere->OnComponentEndOverlap.AddDynamic(this, &ABaseItemActor::OnEndOverlap);
}

void ABaseItemActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABaseCharacter* PlayerCharacter = Cast<ABaseCharacter>(OtherActor))
	{
		if (PlayerCharacter->IsLocallyControlled()) {HighlightActor();}
		PlayerCharacter->SetOverlappingActor(this);
	}
}

void ABaseItemActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ABaseCharacter* PlayerCharacter = Cast<ABaseCharacter>(OtherActor))
	{
		if (PlayerCharacter->IsLocallyControlled()) {UnHighlightActor();}
		PlayerCharacter->SetOverlappingActor(nullptr);
	}
}

void ABaseItemActor::InteractWith(ABaseCharacter* PlayerCharacter)
{
}

void ABaseItemActor::HighlightActor()
{
	ItemMesh->SetRenderCustomDepth(true);
	ItemMesh->SetCustomDepthStencilValue(250);
}

void ABaseItemActor::UnHighlightActor()
{
	ItemMesh->SetRenderCustomDepth(false);
	ItemMesh->SetCustomDepthStencilValue(0);
}
