// Fill out your copyright notice in the Description page of Project Settings.


#include "Mushroom.h"

AMushroom::AMushroom()
{
    Speed = 50.0f;
    GetCharacterMovement()->MaxWalkSpeed = Speed; 
    Health = 100.0f;
    bIsDead = false;

    GetSprite()->SetRelativeScale3D(FVector(0.75f, 0.75f, 0.75f));

    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> LeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/AngryMushroom/LeftDown/LeftDown.LeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> RightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/AngryMushroom/RightUp/RightUp.RightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/AngryMushroom/IdleLeftDown/IdleLeftDown.IdleLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/AngryMushroom/IdleRightUp/IdleRightUp.IdleRightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> AttackLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/AngryMushroom/AttackingLeftDown/AttackLeftDown.AttackLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> AttackRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/AngryMushroom/AttackingRightUp/AttackRightUp.AttackRightUp'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieLeftDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/AngryMushroom/DieLeftDown/DieLeftDown.DieLeftDown'"));
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> DieRightUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/AnimatedSprites/MobAnimation/AngryMushroom/DieRightUp/DieRightUp.DieRightUp'"));

    DirectionToMushroomSprite.Add(EMobState::LeftDown, LeftDown.Object);
    DirectionToMushroomSprite.Add(EMobState::RightUp, RightUp.Object);
    DirectionToMushroomSprite.Add(EMobState::IdleLeftDown, IdleLeftDown.Object);
    DirectionToMushroomSprite.Add(EMobState::IdleRightUp, IdleRightUp.Object);
    DirectionToMushroomSprite.Add(EMobState::AttackLeftDown, AttackLeftDown.Object);
    DirectionToMushroomSprite.Add(EMobState::AttackRightUp, AttackRightUp.Object);
    DirectionToMushroomSprite.Add(EMobState::DieLeftDown, DieLeftDown.Object);
    DirectionToMushroomSprite.Add(EMobState::DieRightUp, DieRightUp.Object);
}

void AMushroom::BeginPlay()
{
    Super::BeginPlay();
    if (World != nullptr) {
        World->AddActor("Mob", this);
        //UE_LOG(LogTemp, Warning, TEXT("World is not a null, added skeleton"));
    } else {
        //UE_LOG(LogTemp, Warning, TEXT("World is null"));
    }

    //UE_LOG(LogTemp, Warning, TEXT("AMushroom spawned"));
}

void AMushroom::Tick(float Deltatime)
{
    Super::Tick(Deltatime);
    UpdateMobState();
}

void AMushroom::UpdateMobSprite()
{
    if(GetbIsDead()){
        return;
    }
    SetMobSprite(MobState);
}

void AMushroom::SetMobSprite(EMobState MobState)
{
    UPaperFlipbook* TemporarySprite = DirectionToMushroomSprite[MobState];
    if (MobFlipbookComponent != nullptr && TemporarySprite != nullptr)
    {
        MobFlipbookComponent->SetFlipbook(TemporarySprite);
    }
}