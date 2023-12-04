// Hunter Game by Gamer Guru.


#include "Actor/Shop/Shop.h"
#include "Character/BaseCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"

AShop::AShop()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root Component")));
	
	ShopkeeperMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShopkeeperMesh"));
	ShopkeeperMesh->SetupAttachment(GetRootComponent());
	ShopkeeperMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	ShopkeeperMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap Box"));
	OverlapBox->SetupAttachment(ShopkeeperMesh);

	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interact Widget"));
	InteractWidget->SetupAttachment(ShopkeeperMesh);
	InteractWidget->SetVisibility(false);
}

void AShop::BeginPlay()
{
	Super::BeginPlay();

	if (OverlapBox)
	{
		OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AShop::OnBoxOverlap);
		OverlapBox->OnComponentEndOverlap.AddDynamic(this, &AShop::OnBoxEndOverlap);
	}
}

void AShop::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABaseCharacter* PlayerCharacter = Cast<ABaseCharacter>(OtherActor))
	{
		PlayerCharacter->SetOverlappingActor(this);

		if (PlayerCharacter->IsLocallyControlled())
		{
			if (InteractWidget)
			{
				InteractWidget->SetVisibility(true);
			}
		}
	}
}

void AShop::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ABaseCharacter* PlayerCharacter = Cast<ABaseCharacter>(OtherActor))
	{
		PlayerCharacter->SetOverlappingActor(nullptr);
		
		if (PlayerCharacter->IsLocallyControlled())
		{
			if (InteractWidget)
			{
				InteractWidget->SetVisibility(false);
			}
		}
	}
}

void AShop::InteractWith(ABaseCharacter* PlayerCharacter)
{
	// TODO: Implement Shop Interaction System
}
