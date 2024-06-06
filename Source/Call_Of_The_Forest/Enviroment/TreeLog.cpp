// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeLog.h"

ATreeLog::ATreeLog()
{
    Health = 150.0f;
    TreeLogComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("TreeLogComponent"));
    ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> AppleTreeAsset(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/tree_log_flipbook.tree_log_flipbook'"));
    TreeLogComponent->SetFlipbook(AppleTreeAsset.Get());
    SetActorScale3D(FVector(0.75, 1.5, 15));
    TreeLogComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    TreeLogComponent->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
    TreeLogComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    TreeLogComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
    TreeLogComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    TreeLogComponent->CanCharacterStepUpOn = ECB_No;
    SetRootComponent(TreeLogComponent);
}