// Fill out your copyright notice in the Description page of Project Settings.


#include "Wolf.h"

AWolf::AWolf()
{
    Speed = 50.0f;
    GetCharacterMovement()->MaxWalkSpeed = Speed;  // Adjust this value as needed
    Health = 100.0f;

    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> LeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Predators/Wolf/LeftDown/LeftDown.LeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> RightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Predators/Wolf/RightUp/RightUp.RightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Predators/Wolf/IdleLeftDown/IdleLeftDown.IdleLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Predators/Wolf/IdleRightUp/IdleRightUp.IdleRightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> AttackingLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Predators/Wolf/AttackLeftDown/AttackLeftDown.AttackLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> AttackingRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Predators/Wolf/AttackRightUp/AttackRightUp.AttackRightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> HitLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Predators/Wolf/HitLeftDown/HitLeftDown.HitLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> HitRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Predators/Wolf/HitRightUp/HitRightUp.HitRightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Predators/Wolf/DieLeftDown/DieLeftDown.DieLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Predators/Wolf/DieRightUp/DieRightUp.DieRightUp'"));

    DirectionToWolfSprite.Add(EPredatorState::LeftDown, LeftDown.Object);
    DirectionToWolfSprite.Add(EPredatorState::RightUp, RightUp.Object);
    DirectionToWolfSprite.Add(EPredatorState::IdleLeftDown, IdleLeftDown.Object);
    DirectionToWolfSprite.Add(EPredatorState::IdleRightUp, IdleRightUp.Object);
    DirectionToWolfSprite.Add(EPredatorState::AttackingLeftDown, LeftDown.Object);
    DirectionToWolfSprite.Add(EPredatorState::AttackingRightUp, RightUp.Object);
    DirectionToWolfSprite.Add(EPredatorState::HitLeftDown, LeftDown.Object);
    DirectionToWolfSprite.Add(EPredatorState::HitRightUp, RightUp.Object);
    DirectionToWolfSprite.Add(EPredatorState::DieLeftDown, DieLeftDown.Object);
    DirectionToWolfSprite.Add(EPredatorState::DieRightUp, DieRightUp.Object);
}

void AWolf::BeginPlay(){
    Super::BeginPlay();
    if (World != nullptr) {
        World->AddActor("Wolf", this);
        UE_LOG(LogTemp, Warning, TEXT("World is not a null, added wolf"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("World is null"));
    }

    UE_LOG(LogTemp, Warning, TEXT("WolfSpawned"));
}

void AWolf::Tick(float Deltatime)
{
    Super::Tick(Deltatime);
    UpdatePredatorState();
}

void AWolf::UpdatePredatorSprite()
{
    if(Health <= 0.0f){
        Die();
    }
    else if(GetVelocity().IsNearlyZero() && (!bIsDead))
    {
        PredatorState = LastPredatorState;
    }
    SetPredatorSprite(PredatorState);
}

void AWolf::SetPredatorSprite(EPredatorState PredatorState)
{
    UPaperFlipbook* TemporarySprite = DirectionToWolfSprite[PredatorState];
    if (PredatorFlipbookComponent != nullptr && TemporarySprite != nullptr)
    {
        PredatorFlipbookComponent->SetFlipbook(TemporarySprite);
    }
}

void AWolf::Die()
{
    if(Health <= 0.0f)
    {
        bIsDead = true;
        PredatorState = (LastPredatorState == EPredatorState::IdleLeftDown) ? EPredatorState::DieLeftDown : EPredatorState::DieRightUp;
        SetPredatorSprite(PredatorState);
    }
}