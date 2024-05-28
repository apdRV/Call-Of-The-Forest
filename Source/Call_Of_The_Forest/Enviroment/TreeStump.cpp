// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeStump.h"

ATreeStump::ATreeStump()
{
    TreeStumpComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("TreeStumpComponent"));
    ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> AppleTreeAsset(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/stump_flipbook.stump_flipbook'"));
    TreeStumpComponent->SetFlipbook(AppleTreeAsset.Get());
    SetActorScale3D(FVector(0.75, 1.5, 15));
    TreeStumpComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    TreeStumpComponent->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
    TreeStumpComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    TreeStumpComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
    TreeStumpComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    TreeStumpComponent->CanCharacterStepUpOn = ECB_No;
    SetRootComponent(TreeStumpComponent);   
}
