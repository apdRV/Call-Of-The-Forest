#include "Meat.h"
#include "../../Inventory/InventoryController.h"
#include "Templates/Casts.h"

AMeat::AMeat()
{
    MeatComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("Meat"));

    ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> MeatSprite(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/meatFlipBook.meatFlipBook'"));

    MeatComponent->SetFlipbook(MeatSprite.Get());
    SetRootComponent(MeatComponent);
    SetActorRotation(FRotator(0, 90, -90));
	SetActorRelativeScale3D(FVector(0.5, 1.0, 0.5));

    ItemID = FName("4");

    Super::Name = "Meat";
    Super::Action = "pickup";
}

void AMeat::Interact_Implementation(APlayerController* Controller)
{
    Super::Interact_Implementation(Controller);

    AInventoryController* IController = Cast<AInventoryController>(Controller);
    if(IController->AddItemToInventoryByID(ItemID))
        Destroy();
}

void AMeat::BeginPlay()
{
    Super::BeginPlay();

}

