// Fill out your copyright notice in the Description page of Project Settings.


#include "Bush.h"

ABush::ABush()
{
    Health = 100.0f;
    BushComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("BushComponent"));
    ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> AppleTreeAsset(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/BushFlipbook.BushFlipbook'"));
    BushComponent->SetFlipbook(AppleTreeAsset.Get());
    SetActorScale3D(FVector(0.75, 1.5, 15));
    BushComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BushComponent->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
    BushComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    BushComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
    BushComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    BushComponent->CanCharacterStepUpOn = ECB_No;
    SetRootComponent(BushComponent);
}