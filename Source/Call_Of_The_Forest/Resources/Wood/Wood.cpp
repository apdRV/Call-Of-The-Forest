#include "Wood.h"
#include "../../Inventory/InventoryController.h"
#include "Templates/Casts.h"

AWood::AWood()
{
    WoodComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("Wood"));

    ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> WoodSprite(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/logFlipBook.logFlipBook'"));

    WoodComponent->SetFlipbook(WoodSprite.Get());
    SetRootComponent(WoodComponent);
    SetActorRotation(FRotator(0, 0, 90));
	SetActorRelativeScale3D(FVector(0.5, 1.0, 0.5));

    Value = 1 + std::rand() % 2;
}



