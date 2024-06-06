// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleTree.h"

ASimpleTree::ASimpleTree()
{
    Health = 300.0f;
    SimpleTreeComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("SimpleTreeComponent"));
    ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> AppleTreeAsset(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/tree_Flipbook.tree_Flipbook'"));
    SimpleTreeComponent->SetFlipbook(AppleTreeAsset.Get());
    SetActorScale3D(FVector(0.75, 1.5, 15));
    SimpleTreeComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    SimpleTreeComponent->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
    SimpleTreeComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    SimpleTreeComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
    SimpleTreeComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    SimpleTreeComponent->CanCharacterStepUpOn = ECB_No;
    SetRootComponent(SimpleTreeComponent);    
}