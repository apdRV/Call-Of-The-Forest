// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterSpriteComponent.h"

UMainCharacterSpriteComponent::UMainCharacterSpriteComponent()
{
    CurrentSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("Spawn_sprite"));


    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/IdleDown.IdleDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/IdleUp.IdleUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleLeft(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/IdleLeft.IdleLeft'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleRight(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/IdleRight.IdleRight'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> UpSprite(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/WalkingUp.WalkingUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DownSprite(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/WalkingDown1.WalkingDown1'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> LeftSprite(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/WalkingRight.WalkingRight'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> RightSprite(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/WalkingRight.WalkingRight'"));

    DirectionToSprite.Add(EMainCharacterDirection::Up, UpSprite.Object);
    DirectionToSprite.Add(EMainCharacterDirection::Down, DownSprite.Object);
    DirectionToSprite.Add(EMainCharacterDirection::Left, LeftSprite.Object);
    DirectionToSprite.Add(EMainCharacterDirection::Right, RightSprite.Object);
    DirectionToSprite.Add(EMainCharacterDirection::IdleUp, IdleUp.Object);
    DirectionToSprite.Add(EMainCharacterDirection::IdleDown, IdleDown.Object);
    DirectionToSprite.Add(EMainCharacterDirection::IdleLeft, IdleLeft.Object);
    DirectionToSprite.Add(EMainCharacterDirection::IdleRight, IdleRight.Object);
}

void UMainCharacterSpriteComponent::UpdateSprite(EMainCharacterDirection Direction)
{
    UPaperFlipbook* Sprite = DirectionToSprite[Direction];
    if (CurrentSprite != nullptr && Sprite != nullptr)
    {
        CurrentSprite->SetFlipbook(Sprite);
    }
}

void UMainCharacterSpriteComponent::SetupOwner(UPaperFlipbookComponent *Owner)
{
    CurrentSprite = Owner;
}
