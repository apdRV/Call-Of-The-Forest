// Fill out your copyright notice in the Description page of Project Settings.


#include "MobFlipbookComponent.h"

UMobFlipbookComponent::UMobFlipbookComponent(){
    MobSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("Mob_spawn_sprite"));

    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> LeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/SkeletonAnimation/LeftDown/LeftDown.LeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> RightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/SkeletonAnimation/RightUp/RightUp.RightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/SkeletonAnimation/IdleLeftDown/IdleLeftDown.IdleLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/SkeletonAnimation/IdleRightUp/IdleRightUp.IdleRightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> AttackLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/SkeletonAnimation/AttackingLeftDown/AttackingLeftDown.AttackingLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> AttackRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/SkeletonAnimation/AttackingRightUp/AttackingRightUp.AttackingRightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/SkeletonAnimation/DieLeftDown/DieLeftDown.DieLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/SkeletonAnimation/DieRightUp/DieRightUp.DieRightUp'"));

    DirectionToSprite.Add(EMobState::LeftDown, LeftDown.Object);
    DirectionToSprite.Add(EMobState::RightUp, RightUp.Object);
    DirectionToSprite.Add(EMobState::IdleLeftDown, IdleLeftDown.Object);
    DirectionToSprite.Add(EMobState::IdleRightUp, IdleRightUp.Object);
    DirectionToSprite.Add(EMobState::AttackLeftDown, AttackLeftDown.Object);
    DirectionToSprite.Add(EMobState::AttackRightUp, AttackRightUp.Object);
    DirectionToSprite.Add(EMobState::DieLeftDown, DieLeftDown.Object);
    DirectionToSprite.Add(EMobState::DieRightUp, DieRightUp.Object);
}

void UMobFlipbookComponent::UpdateSprite(EMobState State)
{
    UPaperFlipbook* TemporarySprite = DirectionToSprite[State];
    if (MobSprite != nullptr && TemporarySprite != nullptr)
    {
        MobSprite->SetFlipbook(TemporarySprite);
    }
}

void UMobFlipbookComponent::SetupOwner(UPaperFlipbookComponent *Owner)
{
    MobSprite = Owner;
}