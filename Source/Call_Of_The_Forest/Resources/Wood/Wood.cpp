#include "Wood.h"
#include "Templates/Casts.h"

AWood::AWood()
{
    WoodComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("Wood"));

    ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> WoodSprite(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/logFlipBook.logFlipBook'"));

    WoodComponent->SetFlipbook(WoodSprite.Get());
    SetRootComponent(WoodComponent);
    SetActorRotation(FRotator(0, 90, -90));
	SetActorRelativeScale3D(FVector(1.0, 2.0, 1.0));

    Value = 1 + std::rand() % 2;
}

