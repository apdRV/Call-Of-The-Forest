#include "Wood.h"
#include <iostream>

AWood::AWood()
{
    Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(FName("Wood"));

    ConstructorHelpers::FObjectFinder<UPaperSprite> WoodSprite(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/log.log'"));

    if (WoodSprite.Succeeded())
    {
        Sprite->SetSprite(WoodSprite.Object);
        SetRootComponent(Sprite);
    }
}


void AWood::BeginPlay()
{
    Super::BeginPlay();
    SetActorScale3D(FVector(0.5, 1, 0.4));
}

