#include "Wood.h"
#include "../Inventory/InventoryController.h"

AWood::AWood()
{
    WoodComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("Wood"));

    ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> WoodSprite(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/logFlipBook.logFlipBook'"));

    WoodComponent->SetFlipbook(WoodSprite.Get());
    SetRootComponent(WoodComponent);
    SetActorRotation(FRotator(0, 0, 90));
	SetActorRelativeScale3D(FVector(0.5, 1.0, 0.5));

    ItemID = FName("2");

    Super::Name = "Wood";
    Super::Action = "pickup";
}

void AWood::Interact_Implementation(APlayerController* Controller)
{
    Super::Interact_Implementation(Controller);

    AInventoryController* IController = Cast(Controller);
    if(IController->AddItemToInventoryByID(ItemID))
        Destroy();
}


void AWood::BeginPlay()
{
    Super::BeginPlay();

}

