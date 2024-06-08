// Fill out your copyright notice in the Description page of Project Settings.


#include "MSkeleton.h"

AMSkeleton::AMSkeleton()
{
    Speed = 50.0f;
    GetCharacterMovement()->MaxWalkSpeed = Speed;  // Adjust this value as needed
    Health = 200.0f;
    BaseDamage = 20.0f;
    bIsDead = false;

    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> LeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/SkeletonAnimation/LeftDown/LeftDown.LeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> RightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/SkeletonAnimation/RightUp/RightUp.RightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/SkeletonAnimation/IdleLeftDown/IdleLeftDown.IdleLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/SkeletonAnimation/IdleRightUp/IdleRightUp.IdleRightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> AttackLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/SkeletonAnimation/AttackingLeftDown/AttackingLeftDown.AttackingLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> AttackRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/SkeletonAnimation/AttackingRightUp/AttackingRightUp.AttackingRightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/SkeletonAnimation/DieLeftDown/DieLeftDown.DieLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/SkeletonAnimation/DieRightUp/DieRightUp.DieRightUp'"));

    DirectionToSkeletonSprite.Add(EMobState::LeftDown, LeftDown.Object);
    DirectionToSkeletonSprite.Add(EMobState::RightUp, RightUp.Object);
    DirectionToSkeletonSprite.Add(EMobState::IdleLeftDown, IdleLeftDown.Object);
    DirectionToSkeletonSprite.Add(EMobState::IdleRightUp, IdleRightUp.Object);
    DirectionToSkeletonSprite.Add(EMobState::AttackLeftDown, AttackLeftDown.Object);
    DirectionToSkeletonSprite.Add(EMobState::AttackRightUp, AttackRightUp.Object);
    DirectionToSkeletonSprite.Add(EMobState::DieLeftDown, DieLeftDown.Object);
    DirectionToSkeletonSprite.Add(EMobState::DieRightUp, DieRightUp.Object);
}

void AMSkeleton::BeginPlay()
{
    Super::BeginPlay();
    if (World != nullptr) {
        World->AddActor("Mob", this);
        //UE_LOG(LogTemp, Warning, TEXT("World is not a null, added skeleton"));
    } else {
        //UE_LOG(LogTemp, Warning, TEXT("World is null"));
    }

    //UE_LOG(LogTemp, Warning, TEXT("SkeletonSpawned"));
}

void AMSkeleton::Tick(float Deltatime)
{
    Super::Tick(Deltatime);
    UpdateMobState();
}

void AMSkeleton::UpdateMobSprite()
{
    if(GetbIsDead()){
        return;
    }
    SetMobSprite(MobState);
}

void AMSkeleton::SetMobSprite(EMobState MobState)
{
    UPaperFlipbook* TemporarySprite = DirectionToSkeletonSprite[MobState];
    if (MobFlipbookComponent != nullptr && TemporarySprite != nullptr)
    {
        MobFlipbookComponent->SetFlipbook(TemporarySprite);
    }
}
