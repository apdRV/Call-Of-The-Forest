// Fill out your copyright notice in the Description page of Project Settings.


#include "AppleTree.h"

AAppleTree::AAppleTree()
{
    AppleTreeComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("AppleTreeComponent"));
    ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> AppleTreeAsset(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/AppleTree_Filpbook.AppleTree_Filpbook'"));
    AppleTreeComponent->SetFlipbook(AppleTreeAsset.Get());
    SetActorScale3D(FVector(0.75, 1.5, 15));
    AppleTreeComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    AppleTreeComponent->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
    AppleTreeComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    AppleTreeComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
    AppleTreeComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    AppleTreeComponent->CanCharacterStepUpOn = ECB_No;
    SetRootComponent(AppleTreeComponent);
}