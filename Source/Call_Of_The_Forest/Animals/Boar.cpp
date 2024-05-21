// Fill out your copyright notice in the Description page of Project Settings.


#include "Boar.h"

ABoar::ABoar(){
    bSpeed = 50.0f;
    GetCharacterMovement()->MaxWalkSpeed = bSpeed;  // Adjust this value as needed
    bHealth = 200.0f;
    bIsDead = false;

    GetSprite()->SetRelativeScale3D(FVector(1.25f, 1.25f, 1.25f));

    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> LeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Boar/WalkingLeftDown/LeftDown.LeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> RightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Boar/WalkingRightUp/RightUp.RightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Boar/IdleLeftDown/IdleLeftDown.IdleLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Boar/IdleRightUp/IdleRightUp.IdleRightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Boar/DeathLeftDown/DeathLeftDown.DeathLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Boar/DeathRightUp/DeathRightUp.DeathRightUp'"));

    DirectionToBoarSprite.Add(EAnimalState::LeftDown, LeftDown.Object);
    DirectionToBoarSprite.Add(EAnimalState::RightUp, RightUp.Object);
    DirectionToBoarSprite.Add(EAnimalState::IdleLeftDown, IdleLeftDown.Object);
    DirectionToBoarSprite.Add(EAnimalState::IdleRightUp, IdleRightUp.Object);
    DirectionToBoarSprite.Add(EAnimalState::DieLeftDown, DieLeftDown.Object);
    DirectionToBoarSprite.Add(EAnimalState::DieRightUp, DieRightUp.Object);
}



void ABoar::BeginPlay(){
    Super::BeginPlay();
    if (World != nullptr) {
        World->AddActor("Animal", this);
        UE_LOG(LogTemp, Warning, TEXT("World is not a null, Boar rabbit"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("World is null"));
    }

    UE_LOG(LogTemp, Warning, TEXT("BoarSpawned"));
}

void ABoar::Tick(float Deltatime)
{
    Super::Tick(Deltatime);
    UpdateAnimalState();
}

void ABoar::UpdateAnimalSprite()
{
    if(GetbIsDead()){
        return;
    }
    else if(GetVelocity().IsNearlyZero() && (!bIsDead))
    {
        AnimalState = LastAnimalState;
    }
    SetAnimalSprite(AnimalState);
}

void ABoar::SetAnimalSprite(EAnimalState AnimalState)
{
    UPaperFlipbook* TemporarySprite = DirectionToBoarSprite[AnimalState];
    if (AnimalFlipbookComponent != nullptr && TemporarySprite != nullptr)
    {
        AnimalFlipbookComponent->SetFlipbook(TemporarySprite);
    }
}

void ABoar::Die()
{
    if(bHealth <= 0.0f)
    {
        bIsDead = true;
        AnimalState = (LastAnimalState == EAnimalState::IdleLeftDown) ? EAnimalState::DieLeftDown : EAnimalState::DieRightUp;
        SetAnimalSprite(AnimalState);
        SetbSpeed(0.0f);
    }
}