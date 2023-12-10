// Hunter Game by Gamer Guru.


#include "Actor/BaseItemActor.h"
#include "Character/BaseCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

ABaseItemActor::ABaseItemActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	SetRootComponent(ItemMesh);
	ItemMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Area Sphere"));
	AreaSphere->SetupAttachment(ItemMesh);

	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interact Widget"));
	InteractWidget->SetupAttachment(GetRootComponent());
	InteractWidget->SetVisibility(false);
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
		if (PlayerCharacter->IsLocallyControlled())
		{
			HighlightActor();
			if (InteractWidget) {InteractWidget->SetVisibility(true);}
		}
		PlayerCharacter->SetOverlappingActor(this);
	}
}

void ABaseItemActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ABaseCharacter* PlayerCharacter = Cast<ABaseCharacter>(OtherActor))
	{
		if (PlayerCharacter->IsLocallyControlled())
		{
			UnHighlightActor();
			if (InteractWidget) {InteractWidget->SetVisibility(false);}
		}
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
