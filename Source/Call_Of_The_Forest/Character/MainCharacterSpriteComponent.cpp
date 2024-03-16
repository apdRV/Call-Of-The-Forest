// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterSpriteComponent.h"

UMainCharacterSpriteComponent::UMainCharacterSpriteComponent()
{
    MainCharacterSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("Spawn_sprite"));


    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/IdleDown/IdleDown.IdleDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/IdleUp/IdleUp.IdleUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleLeft(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/IdleLeft/IdleLeft.IdleLeft'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleRight(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/IdleRight/IdleRight.IdleRight'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> UpSprite(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/WalkingUp/WalkingUp.WalkingUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DownSprite(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/WalkingDown/WalkingDown.WalkingDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> LeftSprite(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/WalkingLeft/WalkingLeft.WalkingLeft'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> RightSprite(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/WalkingRight/WalkingRight.WalkingRight'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> AttackUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/AttackingUp/AttackingUp.AttackingUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> AttackDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/AttackingDown/AttackingDown.AttackingDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> AttackLeft(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/AttackingLeft/AttackingLeft.AttackingLeft'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> AttackRight(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/AttackingRight/AttackingRight.AttackingRight'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieLeft(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/DieLeft/DieLeft.DieLeft'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieRight(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/DieRight/DieRight.DieRight'"));

    DirectionToSprite.Add(EMainCharacterState::Up, UpSprite.Object);
    DirectionToSprite.Add(EMainCharacterState::Down, DownSprite.Object);
    DirectionToSprite.Add(EMainCharacterState::Left, LeftSprite.Object);
    DirectionToSprite.Add(EMainCharacterState::Right, RightSprite.Object);
    DirectionToSprite.Add(EMainCharacterState::IdleUp, IdleUp.Object);
    DirectionToSprite.Add(EMainCharacterState::IdleDown, IdleDown.Object);
    DirectionToSprite.Add(EMainCharacterState::IdleLeft, IdleLeft.Object);
    DirectionToSprite.Add(EMainCharacterState::IdleRight, IdleRight.Object);
    DirectionToSprite.Add(EMainCharacterState::AttackUp, AttackUp.Object);
    DirectionToSprite.Add(EMainCharacterState::AttackDown, AttackDown.Object);
    DirectionToSprite.Add(EMainCharacterState::AttackLeft, AttackLeft.Object);
    DirectionToSprite.Add(EMainCharacterState::AttackRight, AttackRight.Object);
    DirectionToSprite.Add(EMainCharacterState::DieLeft, DieLeft.Object);
    DirectionToSprite.Add(EMainCharacterState::DieRight, DieRight.Object);
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
