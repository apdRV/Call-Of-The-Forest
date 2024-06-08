// Fill out your copyright notice in the Description page of Project Settings.


#include "Rock.h"

ARock::ARock()
{
    Health = 250.0f;
    RockComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("RockComponent"));
    ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> AppleTreeAsset(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/StoneMap_Flipbook.StoneMap_Flipbook'"));
    RockComponent->SetFlipbook(AppleTreeAsset.Get());
    SetActorScale3D(FVector(0.75, 1.5, 15));
    RockComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    RockComponent->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
    RockComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    RockComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
    RockComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    RockComponent->CanCharacterStepUpOn = ECB_No;
    SetRootComponent(RockComponent);
}