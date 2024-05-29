// Fill out your copyright notice in the Description page of Project Settings.


#include "Rabbit.h"

ARabbit::ARabbit(){
    bSpeed = 50.0f;
    GetCharacterMovement()->MaxWalkSpeed = bSpeed;
    bHealth = 100.0f;
    bIsDead = false;

    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> LeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Rabbit/WalkingLeftDown/LeftDown.LeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> RightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Rabbit/WalkingRightUp/RightUp.RightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Rabbit/IdleLeftDown/IdleLeftDown.IdleLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Rabbit/IdleRightUp/IdleRightUp.IdleRightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Rabbit/DeathLeftDown/DeathLeftDown.DeathLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Rabbit/DeathRightUp/DeathRightUp.DeathRightUp'"));

    DirectionToRabbitSprite.Add(EAnimalState::LeftDown, LeftDown.Object);
    DirectionToRabbitSprite.Add(EAnimalState::RightUp, RightUp.Object);
    DirectionToRabbitSprite.Add(EAnimalState::IdleLeftDown, IdleLeftDown.Object);
    DirectionToRabbitSprite.Add(EAnimalState::IdleRightUp, IdleRightUp.Object);
    DirectionToRabbitSprite.Add(EAnimalState::DieLeftDown, DieLeftDown.Object);
    DirectionToRabbitSprite.Add(EAnimalState::DieRightUp, DieRightUp.Object);
}

void ARabbit::BeginPlay(){
    Super::BeginPlay();
    if (World != nullptr) {
        World->AddActor("Animal", this);
        UE_LOG(LogTemp, Warning, TEXT("World is not a null, added rabbit"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("World is null"));
    }

    UE_LOG(LogTemp, Warning, TEXT("RabbitSpawned"));
}

void ARabbit::Tick(float Deltatime)
{
    Super::Tick(Deltatime);
    UpdateAnimalState();
}

void ARabbit::UpdateAnimalSprite()
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

void ARabbit::SetAnimalSprite(EAnimalState AnimalState)
{
    UPaperFlipbook* TemporarySprite = DirectionToRabbitSprite[AnimalState];
    if (AnimalFlipbookComponent != nullptr && TemporarySprite != nullptr)
    {
        AnimalFlipbookComponent->SetFlipbook(TemporarySprite);
    }
}

void ARabbit::Die()
{
    if(bHealth <= 0.0f)
    {
        bIsDead = true;
        AnimalState = (LastAnimalState == EAnimalState::IdleLeftDown || LastAnimalState == EAnimalState::LeftDown) ? EAnimalState::DieLeftDown : EAnimalState::DieRightUp;
        SetAnimalSprite(AnimalState);
        SetbSpeed(0.0f);
    }
}