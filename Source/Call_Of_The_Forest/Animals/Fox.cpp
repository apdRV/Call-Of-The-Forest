// Fill out your copyright notice in the Description page of Project Settings.


#include "Fox.h"

AFox::AFox()
{
    Speed = 0.05f;
    Health = 200.0f;
    bIsDead = false;

    GetSprite()->SetRelativeScale3D(FVector(1.1f, 1.1f, 1.1f));

    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> LeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Boar/WalkingLeftDown/LeftDown.LeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> RightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Boar/WalkingRightUp/RightUp.RightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Boar/IdleLeftDown/IdleLeftDown.IdleLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Boar/IdleRightUp/IdleRightUp.IdleRightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Boar/DeathLeftDown/DeathLeftDown.DeathLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Boar/DeathRightUp/DeathRightUp.DeathRightUp'"));

    DirectionToFoxSprite.Add(EAnimalState::LeftDown, LeftDown.Object);
    DirectionToFoxSprite.Add(EAnimalState::RightUp, RightUp.Object);
    DirectionToFoxSprite.Add(EAnimalState::IdleLeftDown, IdleLeftDown.Object);
    DirectionToFoxSprite.Add(EAnimalState::IdleRightUp, IdleRightUp.Object);
    DirectionToFoxSprite.Add(EAnimalState::DieLeftDown, DieLeftDown.Object);
    DirectionToFoxSprite.Add(EAnimalState::DieRightUp, DieRightUp.Object);

}

void AFox::BeginPlay(){
    Super::BeginPlay();
    if (World != nullptr) {
        World->AddActor("Fox", this);
        UE_LOG(LogTemp, Warning, TEXT("World is not a null, added fox"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("World is null"));
    }

    UE_LOG(LogTemp, Warning, TEXT("FoxSpawned"));
}

void AFox::Tick(float Deltatime)
{
    Super::Tick(Deltatime);
    UpdateAnimalState();
}

void AFox::UpdateAnimalSprite()
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

void AFox::SetAnimalSprite(EAnimalState AnimalState)
{
    UPaperFlipbook* TemporarySprite = DirectionToFoxSprite[AnimalState];
    if (AnimalFlipbookComponent != nullptr && TemporarySprite != nullptr)
    {
        AnimalFlipbookComponent->SetFlipbook(TemporarySprite);
    }
}

void AFox::Die()
{
    if(Health <= 0.0f)
    {
        bIsDead = true;
        AnimalState = (LastAnimalState == EAnimalState::IdleLeftDown) ? EAnimalState::DieLeftDown : EAnimalState::DieRightUp;
        SetAnimalSprite(AnimalState);
    }
}

