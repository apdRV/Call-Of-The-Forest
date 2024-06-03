// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceBase.h"
#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "Math/UnrealMathUtility.h"
#include "../../Character/MainPaperCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Components/SphereComponent.h"

AResourceBase::AResourceBase(){
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
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
        Player->WoodQuantity += FMath::RandRange(1, 3);
    }
    else if (ResourceName == "Stone"){
        Player->StoneQuantity += FMath::RandRange(1, 2);
    }
    else if (ResourceName == "Trophy"){
        Player->TrophyQuantity += 1;
    }
    else if (ResourceName == "Meat"){
        Player->MeatQuantity += FMath::RandRange(1, 2);
    }
    Destroy();
}

