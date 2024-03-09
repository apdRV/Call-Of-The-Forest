// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterSpriteComponent.h"

UMainCharacterSpriteComponent::UMainCharacterSpriteComponent()
{
    MainCharacterSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("Spawn_sprite"));


    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/IdleDown.IdleDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/IdleUp.IdleUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleLeft(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/IdleLeft.IdleLeft'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleRight(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/IdleRight.IdleRight'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> UpSprite(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/WalkingUp.WalkingUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DownSprite(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/WalkingDown1.WalkingDown1'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> LeftSprite(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/WalkingRight.WalkingRight'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> RightSprite(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/WalkingRight.WalkingRight'"));

    DirectionToSprite.Add(EMainCharacterState::Up, UpSprite.Object);
    DirectionToSprite.Add(EMainCharacterState::Down, DownSprite.Object);
    DirectionToSprite.Add(EMainCharacterState::Left, LeftSprite.Object);
    DirectionToSprite.Add(EMainCharacterState::Right, RightSprite.Object);
    DirectionToSprite.Add(EMainCharacterState::IdleUp, IdleUp.Object);
    DirectionToSprite.Add(EMainCharacterState::IdleDown, IdleDown.Object);
    DirectionToSprite.Add(EMainCharacterState::IdleLeft, IdleLeft.Object);
    DirectionToSprite.Add(EMainCharacterState::IdleRight, IdleRight.Object);
}

void UMainCharacterSpriteComponent::UpdateSprite(EMainCharacterState State)
{
    UPaperFlipbook* TemporarySprite = DirectionToSprite[State];
    if (MainCharacterSprite != nullptr && TemporarySprite != nullptr)
    {
        MainCharacterSprite->SetFlipbook(TemporarySprite);
    }
}

void UMainCharacterSpriteComponent::SetupOwner(UPaperFlipbookComponent *Owner)
{
    MainCharacterSprite = Owner;
}
