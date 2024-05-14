// Fill out your copyright notice in the Description page of Project Settings.


#include "Fox.h"

AFox::AFox()
{
    Speed = 60.0f;
    GetCharacterMovement()->MaxWalkSpeed = Speed;  // Adjust this value as needed
    Health = 100.0f;
    bIsDead = false;

    GetSprite()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> LeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Fox/WalkingLeftDown/WalkingLeftDown.WalkingLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> RightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Fox/WalkingRightUp/WalkingRightUp.WalkingRightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Fox/IdleLeftDown/IdleLeftDown.IdleLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Fox/IdleRightUp/IdleRightUp.IdleRightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> AttackingLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Fox/AttackingLeftDown/AttackingLeftDown.AttackingLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> AttackingRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Fox/AttackingRightUp/AttackingRightUp.AttackingRightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> HitLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Fox/LookingLeftDown/LookingLeftDown.LookingLeftDown'")); //Looking leftdown
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> HitRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Fox/LookingRightUp/LookingRightUp.LookingRightUp'")); //Looking rightup
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Fox/DieLeftDown/DieLeftDown.DieLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Fox/DieRIghtUp/DieRightUp.DieRightUp'"));

    DirectionToFoxSprite.Add(EPredatorState::LeftDown, LeftDown.Object);
    DirectionToFoxSprite.Add(EPredatorState::RightUp, RightUp.Object);
    DirectionToFoxSprite.Add(EPredatorState::IdleLeftDown, IdleLeftDown.Object);
    DirectionToFoxSprite.Add(EPredatorState::IdleRightUp, IdleRightUp.Object);
    DirectionToFoxSprite.Add(EPredatorState::AttackingLeftDown, AttackingLeftDown.Object);
    DirectionToFoxSprite.Add(EPredatorState::AttackingRightUp, AttackingRightUp.Object);
    DirectionToFoxSprite.Add(EPredatorState::HitLeftDown, HitLeftDown.Object);
    DirectionToFoxSprite.Add(EPredatorState::HitRightUp, HitRightUp.Object);
    DirectionToFoxSprite.Add(EPredatorState::DieLeftDown, DieLeftDown.Object);
    DirectionToFoxSprite.Add(EPredatorState::DieRightUp, DieRightUp.Object);

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
    UpdatePredatorState();
}

void AFox::UpdatePredatorSprite()
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

void AFox::SetPredatorSprite(EPredatorState PredatorState)
{
    UPaperFlipbook* TemporarySprite = DirectionToFoxSprite[PredatorState];
    if (PredatorFlipbookComponent != nullptr && TemporarySprite != nullptr)
    {
        PredatorFlipbookComponent->SetFlipbook(TemporarySprite);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Sprite not found"));
    }
}

void AFox::Die()
{
    if(Health <= 0.0f)
    {
        bIsDead = true;
        PredatorState = (LastPredatorState == EPredatorState::IdleLeftDown) ? EPredatorState::DieLeftDown : EPredatorState::DieRightUp;
        SetPredatorSprite(PredatorState);
    }
}