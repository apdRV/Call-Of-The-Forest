// Fill out your copyright notice in the Description page of Project Settings.


#include "Sprout.h"


ASprout::ASprout()
{
    Speed = 50.0f;
    GetCharacterMovement()->MaxWalkSpeed = Speed;  // Adjust this value as needed
    Health = 100.0f;
    bIsDead = false;

    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> LeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/Sprout/LeftDown/LeftDown.LeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> RightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/Sprout/RightUp/RightUp.RightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/Sprout/IdleLeftDown/IdleLeftDown.IdleLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/Sprout/IdleRightUp/IdleRightUp.IdleRightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> AttackLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/Sprout/AttackLeftDown/AttackLeftDown.AttackLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> AttackRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/Sprout/AttackRightUp/AttackRightUp.AttackRightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/Sprout/DieLeftDown/DieLeftDown.DieLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/Sprout/DieRightUp/DieRightUp.DieRightUp'"));


    DirectionToSproutSprite.Add(EMobState::LeftDown, LeftDown.Object);
    DirectionToSproutSprite.Add(EMobState::RightUp, RightUp.Object);
    DirectionToSproutSprite.Add(EMobState::IdleLeftDown, IdleLeftDown.Object);
    DirectionToSproutSprite.Add(EMobState::IdleRightUp, IdleRightUp.Object);
    DirectionToSproutSprite.Add(EMobState::AttackLeftDown, AttackLeftDown.Object);
    DirectionToSproutSprite.Add(EMobState::AttackRightUp, AttackRightUp.Object);
    DirectionToSproutSprite.Add(EMobState::DieLeftDown, DieLeftDown.Object);
    DirectionToSproutSprite.Add(EMobState::DieRightUp, DieRightUp.Object);
    GetSprite()->SetRelativeScale3D(FVector(0.75f, 0.75f, 0.75f));
}

void ASprout::BeginPlay()
{
    Super::BeginPlay();
    if (World != nullptr) {
        World->AddActor("Mob", this);
        UE_LOG(LogTemp, Warning, TEXT("World is not a null, added sprout"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("World is null"));
    }

    UE_LOG(LogTemp, Warning, TEXT("SproutSpawned"));
}

void ASprout::Tick(float Deltatime)
{
    Super::Tick(Deltatime);
    UpdateMobState();
}

void ASprout::UpdateMobSprite()
{
    if(GetbIsDead())
    {
        return;
    }
    SetMobSprite(MobState);
}

void ASprout::SetMobSprite(EMobState MobState)
{
    UPaperFlipbook* TemporarySprite = DirectionToSproutSprite[MobState];
    if (MobFlipbookComponent != nullptr && TemporarySprite != nullptr)
    {
        MobFlipbookComponent->SetFlipbook(TemporarySprite);
    }
}