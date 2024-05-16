// Fill out your copyright notice in the Description page of Project Settings.


#include "Bear.h"

ABear::ABear()
{
    Speed = 40.0f;
    GetCharacterMovement()->MaxWalkSpeed = Speed;  // Adjust this value as needed
    Health = 200.0f;
    bIsDead = false;

    GetSprite()->SetRelativeScale3D(FVector(1.2f, 1.2f, 1.2f));

    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> LeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Bear/WalkingLeftDown/LeftDown.LeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> RightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Bear/WalkingRightUp/RightUp.RightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Bear/IdleLeftDown/IdleLeftDown.IdleLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Bear/IdleRightUp/IdleRightUp.IdleRightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> AttackingLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Bear/AttackingLeftDown2/AttackingLeftDown2.AttackingLeftDown2'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> AttackingRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Bear/AttackingRightUp2/AttackingRightUp2.AttackingRightUp2'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> HitLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Bear/HitLeftDown/HitLeftDown.HitLeftDown'")); //Looking leftdown
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> HitRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Bear/HitRightUp/HitRightUp.HitRightUp'")); //Looking rightup
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Bear/DeathLeftDown/DeathLeftDown.DeathLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Bear/DeathRightUp/DeathRightUp.DeathRightUp'"));

    DirectionToBearSprite.Add(EPredatorState::LeftDown, LeftDown.Object);
    DirectionToBearSprite.Add(EPredatorState::RightUp, RightUp.Object);
    DirectionToBearSprite.Add(EPredatorState::IdleLeftDown, IdleLeftDown.Object);
    DirectionToBearSprite.Add(EPredatorState::IdleRightUp, IdleRightUp.Object);
    DirectionToBearSprite.Add(EPredatorState::AttackingLeftDown, AttackingLeftDown.Object);
    DirectionToBearSprite.Add(EPredatorState::AttackingRightUp, AttackingRightUp.Object);
    DirectionToBearSprite.Add(EPredatorState::HitLeftDown, HitLeftDown.Object);
    DirectionToBearSprite.Add(EPredatorState::HitRightUp, HitRightUp.Object);
    DirectionToBearSprite.Add(EPredatorState::DieLeftDown, DieLeftDown.Object);
    DirectionToBearSprite.Add(EPredatorState::DieRightUp, DieRightUp.Object);

}

void ABear::BeginPlay(){
    Super::BeginPlay();
    if (World != nullptr) {
        World->AddActor("Predator", this);
        UE_LOG(LogTemp, Warning, TEXT("World is not a null, added bear"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("World is null"));
    }

    UE_LOG(LogTemp, Warning, TEXT("Bear Spawned"));
}

void ABear::Tick(float Deltatime)
{
    Super::Tick(Deltatime);
    UpdatePredatorState();
}

void ABear::UpdatePredatorSprite()
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

void ABear::SetPredatorSprite(EPredatorState PredatorState)
{
    UPaperFlipbook* TemporarySprite = DirectionToBearSprite[PredatorState];
    if (PredatorFlipbookComponent != nullptr && TemporarySprite != nullptr)
    {
        PredatorFlipbookComponent->SetFlipbook(TemporarySprite);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Sprite not found"));
    }
}

void ABear::Die()
{
    if(Health <= 0.0f)
    {
        bIsDead = true;
        PredatorState = (LastPredatorState == EPredatorState::IdleLeftDown) ? EPredatorState::DieLeftDown : EPredatorState::DieRightUp;
        SetPredatorSprite(PredatorState);
    }
}