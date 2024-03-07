#include "Wood.h"

AWood::AWood()
{
    WoodComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("Wood"));

    ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> WoodSprite(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/logFlipBook.logFlipBook'"));

    WoodComponent->SetFlipbook(WoodSprite.Get());
    SetRootComponent(WoodComponent);
    SetActorRotation(FRotator(0, 0, 90));
	SetActorRelativeScale3D(FVector(0.5, 1.0, 0.5));
}


void AWood::BeginPlay()
{
    Super::BeginPlay();

}

