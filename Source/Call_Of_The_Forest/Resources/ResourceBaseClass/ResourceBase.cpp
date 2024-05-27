// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceBase.h"
#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "../../Character/MainPaperCharacter.h"
#include "Components/SphereComponent.h"

AResourceBase::AResourceBase(){
    PrimaryActorTick.bCanEverTick = true;
}

void AResourceBase::BeginPlay(){
    Super::BeginPlay();
}

void AResourceBase::Tick(float DeltaTime){
    Super::Tick(DeltaTime);
}

void AResourceBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
    AMainPaperCharacter* Player = Cast<AMainPaperCharacter>(OtherActor);
    if(Player){
        OnPickup(Player);
    }
}

void AResourceBase::OnPickup(AMainPaperCharacter* Player){
    if (ResourceName == "Wood"){
        Player->WoodQuantity += Value;
    }
    else if (ResourceName == "Stone"){
        Player->StoneQuantity += Value;
    }
    else if (ResourceName == "Trophy"){
        Player->TrophyQuantity += Value;
    }
    else if (ResourceName == "Meat"){
        Player->MeatQuantity += Value;
    }
    Destroy();
}

