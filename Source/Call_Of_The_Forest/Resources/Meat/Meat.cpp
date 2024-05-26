#include "Meat.h"
#include "../../Inventory/InventoryController.h"
#include "Templates/Casts.h"

AMeat::AMeat()
{
    MeatComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("Meat"));

    ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> MeatSprite(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/meatFlipBook.meatFlipBook'"));

    MeatComponent->SetFlipbook(MeatSprite.Get());
    SetRootComponent(MeatComponent);
    SetActorRotation(FRotator(0, 180, 90));
	SetActorRelativeScale3D(FVector(0.5, 1.0, 0.5));

    Value = 1 + std::rand() % 2;
}

