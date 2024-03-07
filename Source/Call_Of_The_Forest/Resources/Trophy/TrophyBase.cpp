// Fill out your copyright notice in the Description page of Project Settings.


#include "TrophyBase.h"

ATrophyBase::ATrophyBase()
{
    TrophyBaseComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("TrophyBase"));

    ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> TrophyBaseSprite(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/trophyFlipBook.trophyFlipBook'"));

    TrophyBaseComponent->SetFlipbook(TrophyBaseSprite.Get());
    SetRootComponent(TrophyBaseComponent);
    SetActorRotation(FRotator(0, 180, 90));
	SetActorRelativeScale3D(FVector(0.5, 1.0, 0.5));
}


void ATrophyBase::BeginPlay()
{
    Super::BeginPlay();

}
