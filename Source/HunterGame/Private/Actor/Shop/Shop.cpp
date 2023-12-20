// Hunter Game by Gamer Guru.


#include "Actor/Shop/Shop.h"
#include "Camera/CameraComponent.h"
#include "Character/BaseCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "HUD/HunterHUD.h"
#include "HUD/ShopUI/ShopMenu.h"
#include "PlayerController/HunterPlayerController.h"

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

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("View Camera"));
	ViewCamera->SetupAttachment(GetRootComponent());

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
	if (ShopMenuUWClass != nullptr)
	{
		ShopMenuUW = CreateWidget<UShopMenu>(GetWorld(), ShopMenuUWClass);

		if (ShopMenuUW)
		{
			ShopMenuUW->Init_Content(ShopContent);
			ShopMenuUW->AddToViewport();
			ShopMenuUW->PlayerCharacter = PlayerCharacter;
			if (PlayerCharacter) {PlayerCharacter->HideCharacterOverlayUI();}
			if (PlayerCharacter->GetCustomPlayerController() && PlayerCharacter->GetCustomPlayerController()->GetHUDReference())
			{
				PlayerCharacter->GetCustomPlayerController()->GetHUDReference()->SetInputModeAsUIOnly();
				PlayerCharacter->GetCustomPlayerController()->SetViewTargetWithBlend(this, 0.25f);
			}
		}
	}
}
