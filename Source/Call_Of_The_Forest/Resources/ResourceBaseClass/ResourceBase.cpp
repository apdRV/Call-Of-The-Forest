// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceBase.h"
#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "../../Character/MainPaperCharacter.h"
#include "Components/SphereComponent.h"

AResourceBase::AResourceBase(){
    PrimaryActorTick.bCanEverTick = true;

    PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickupSphere"));
    PickupSphere->SetSphereRadius(5.f);
    PickupSphere->SetCollisionProfileName(TEXT("Trigger"));

    RootComponent = PickupSphere;

    PickupSphere->OnComponentBeginOverlap.AddDynamic(this, &AResourceBase::OnOverlapBegin);
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
    Destroy();
}

