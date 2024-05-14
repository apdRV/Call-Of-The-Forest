// Fill out your copyright notice in the Description page of Project Settings.


#include "Deer.h"

ADeer::ADeer(){
    Speed = 100.0f;
    GetCharacterMovement()->MaxWalkSpeed = Speed;  // Adjust this value as needed
    Health = 200.0f;
    bIsDead = false;

    GetSprite()->SetRelativeScale3D(FVector(1.25f, 1.25f, 1.25f));

    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> LeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Deer/LeftDown/LeftDown.LeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> RightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Deer/RightUp/RightUp.RightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Deer/IdleLeftDown/IdleLeftDown.IdleLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Deer/IdleRightUp/IdleRightUp.IdleRightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Deer/DieLeftDown/DieLeftDown.DieLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Deer/DieRightUp/DieRightUp.DieRightUp'"));

    DirectionToDeerSprite.Add(EAnimalState::LeftDown, LeftDown.Object);
    DirectionToDeerSprite.Add(EAnimalState::RightUp, RightUp.Object);
    DirectionToDeerSprite.Add(EAnimalState::IdleLeftDown, IdleLeftDown.Object);
    DirectionToDeerSprite.Add(EAnimalState::IdleRightUp, IdleRightUp.Object);
    DirectionToDeerSprite.Add(EAnimalState::DieLeftDown, DieLeftDown.Object);
    DirectionToDeerSprite.Add(EAnimalState::DieRightUp, DieRightUp.Object);
}



void ADeer::BeginPlay(){
    Super::BeginPlay();
    if (World != nullptr) {
        World->AddActor("Animal", this);
        UE_LOG(LogTemp, Warning, TEXT("World is not a null, Deer added"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("World is null"));
    }

    UE_LOG(LogTemp, Warning, TEXT("Deer Spawned"));
}

void ADeer::Tick(float Deltatime)
{
    Super::Tick(Deltatime);
    UpdateAnimalState();
}

void ADeer::UpdateAnimalSprite()
{
    if(Health <= 0.0f){
        Die();
    }
    else if(GetVelocity().IsNearlyZero() && (!bIsDead))
    {
        AnimalState = LastAnimalState;
    }
    SetAnimalSprite(AnimalState);
}

void ADeer::SetAnimalSprite(EAnimalState AnimalState)
{
    UPaperFlipbook* TemporarySprite = DirectionToDeerSprite[AnimalState];
    if (AnimalFlipbookComponent != nullptr && TemporarySprite != nullptr)
    {
        AnimalFlipbookComponent->SetFlipbook(TemporarySprite);
    }
}

void ADeer::Die()
{
    if(Health <= 0.0f)
    {
        bIsDead = true;
        AnimalState = (LastAnimalState == EAnimalState::IdleLeftDown) ? EAnimalState::DieLeftDown : EAnimalState::DieRightUp;
        SetAnimalSprite(AnimalState);
    }
}