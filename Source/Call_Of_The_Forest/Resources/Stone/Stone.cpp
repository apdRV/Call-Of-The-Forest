// Fill out your copyright notice in the Description page of Project Settings.


#include "Stone.h"
#include "Templates/Casts.h"


AStone::AStone()
{
    StoneComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("Stone"));

    ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> StoneSprite(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/stoneFlipBook.stoneFlipBook'"));

    StoneComponent->SetFlipbook(StoneSprite.Get());
    SetRootComponent(StoneComponent);
    SetActorRotation(FRotator(0, 90, -90));
	SetActorRelativeScale3D(FVector(0.5, 1.0, 0.5));

    Value = 1 + std::rand() % 2;
    ResourceName = "Stone";
}

