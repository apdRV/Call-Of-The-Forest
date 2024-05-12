// Fill out your copyright notice in the Description page of Project Settings.


#include "RabbitFlipbookComponent.h"

URabbitFlipbookComponent::URabbitFlipbookComponent()
{
    RabbitSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("Rabbit_sprite"));

    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> LeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Rabbit/WalkingLeftDown/LeftDown.LeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> RightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Rabbit/WalkingRightUp/RightUp.RightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Rabbit/IdleLeftDown/IdleLeftDown.IdleLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Rabbit/IdleRightUp/IdleRightUp.IdleRightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Rabbit/DeathLeftDown/DeathLeftDown.DeathLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/Animals/Rabbit/DeathRightUp/DeathRightUp.DeathRightUp'"));

    DirectionToSprite.Add(ERabbitState::LeftDown, LeftDown.Object);
    DirectionToSprite.Add(ERabbitState::RightUp, RightUp.Object);
    DirectionToSprite.Add(ERabbitState::IdleLeftDown, IdleLeftDown.Object);
    DirectionToSprite.Add(ERabbitState::IdleRightUp, IdleRightUp.Object);
    DirectionToSprite.Add(ERabbitState::DieLeftDown, DieLeftDown.Object);
    DirectionToSprite.Add(ERabbitState::DieRightUp, DieRightUp.Object);
}

void URabbitFlipbookComponent::UpdateSprite(ERabbitState State)
{
    UPaperFlipbook* TemporarySprite = DirectionToSprite[State];
    if (RabbitSprite != nullptr && TemporarySprite != nullptr)
    {
        RabbitSprite->SetFlipbook(TemporarySprite);
    }
}

void URabbitFlipbookComponent::SetupOwner(UPaperFlipbookComponent *Owner)
{
    RabbitSprite = Owner;
}