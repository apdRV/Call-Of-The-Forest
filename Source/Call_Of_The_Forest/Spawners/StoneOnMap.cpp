// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneOnMap.h"

AStoneOnMap::AStoneOnMap(){
    StoneMapComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("stone"));
    	ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> StoneAsset(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/StoneMap_Flipbook.StoneMap_FlipBook'"));
    	StoneMapComponent->SetFlipbook(StoneAsset.Get());
    	SetActorScale3D(FVector(0.75, 1.5, 15));
    	StoneMapComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    	StoneMapComponent->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
    	StoneMapComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    	StoneMapComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
    	StoneMapComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    	StoneMapComponent->CanCharacterStepUpOn = ECB_No;
    	SetRootComponent(StoneMapComponent);
    	World = AStaticWorld::GetStaticWorld();
    	World->AddActor("Stone", this);
}

