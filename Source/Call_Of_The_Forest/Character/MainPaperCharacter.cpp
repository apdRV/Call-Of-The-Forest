// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPaperCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

AMainPaperCharacter::AMainPaperCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

    // Default character properties
	bIsMoving = false;
    bIsDead = false;
    Health = 100.0f;
    CharacterState = EMainCharacterState::IdleDown;
    LastMoveDirection = EMainCharacterState::IdleDown;

    //SpringArm
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeRotation(FRotator(-90.0f, 180.0f, 180.0f));
    CameraBoom->TargetArmLength = 100.f; // расстояние от камеры до игрока
    CameraBoom->bInheritPitch = false;
    CameraBoom->bInheritYaw = false;
    CameraBoom->bInheritRoll = false;


    //Camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    FollowCamera->SetupAttachment(CameraBoom);
    FollowCamera->bUsePawnControlRotation = false;

    // Default capsule component properties
	GetCapsuleComponent()->InitCapsuleSize(10.0f, 10.0f);

    // Default sprite component properties
    GetSprite()->SetRelativeRotation(FRotator(0.0f, 90.0f, -90.0f));
    GetSprite()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

    MainCharacterSpriteComponent = CreateDefaultSubobject<UMainCharacterSpriteComponent>(TEXT("MainCharacterSpriteComponent"));
    MainCharacterSpriteComponent->SetupAttachment(RootComponent);
    MainCharacterSpriteComponent->SetupOwner(GetSprite());
    MainCharacterSpriteComponent->UpdateSprite(CharacterState);
}

// Called every frame
void AMainPaperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    // if ((Controller != nullptr) && (!bIsDead))
    // {
    //     float ForwardBackwardValue = Controller->GetInputAxisValue("MoveForwardBackward");
    //     float RightLeftValue = Controller->GetInputAxisValue("MoveRightLeft");

    //     if (ForwardBackwardValue == 0.0f && RightLeftValue == 0.0f)
    //     {
    //         CharacterState = (LastMoveDirection == EMainCharacterState::Up) ? EMainCharacterState::IdleUp :
    //                          (LastMoveDirection == EMainCharacterState::Down) ? EMainCharacterState::IdleDown :
    //                          (LastMoveDirection == EMainCharacterState::Right) ? EMainCharacterState::IdleRight :
    //                          EMainCharacterState::IdleLeft;  // Default to IdleLeft
    //     }
    //     else
    //     {
    //         if (ForwardBackwardValue != 0.0f)
    //         {
    //             CharacterState = (ForwardBackwardValue > 0) ? EMainCharacterState::Up : EMainCharacterState::Down;
    //             LastMoveDirection = (CharacterState == EMainCharacterState::Up) ? EMainCharacterState::IdleUp : EMainCharacterState::IdleDown;
    //         }
    //         if (RightLeftValue != 0.0f)
    //         {
    //             CharacterState = (RightLeftValue > 0) ? EMainCharacterState::Right : EMainCharacterState::Left;
    //             LastMoveDirection = (CharacterState == EMainCharacterState::Right) ? EMainCharacterState::IdleRight : EMainCharacterState::IdleLeft;
    //         }
    //     }

    //     MainCharacterSpriteComponent->UpdateSprite(CharacterState);
    // }

}

// Called when the game starts or when spawned
void AMainPaperCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// Called to bind functionality to input
void AMainPaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForwardBackward", this, &AMainPaperCharacter::MoveForwardBackward);
    PlayerInputComponent->BindAxis("MoveRightLeft", this, &AMainPaperCharacter::MoveRightLeft);
}

// When W/UP or S/DOWN are pressed
void AMainPaperCharacter::MoveForwardBackward(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f) && (!bIsDead))
    {
        const FVector Direction = FVector(0.5, 0, 0);
        AddMovementInput(Direction, Value);


        CharacterState = (Value > 0) ? EMainCharacterState::Up : EMainCharacterState::Down;
        LastMoveDirection = (CharacterState == EMainCharacterState::Up) ? EMainCharacterState::IdleUp : EMainCharacterState::IdleDown;

        MainCharacterSpriteComponent->UpdateSprite(CharacterState);
    }
    // else if(Value == 0.0f && (Controller == nullptr) && (!bIsDead))
    // {
    //     MainCharacterSpriteComponent->UpdateSprite(LastMoveDirection);
    // }
}

// When A/LEFT or D/RIGHT keys are pressed
void AMainPaperCharacter::MoveRightLeft(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f) && (!bIsDead))
    {
        const FVector Direction = FVector(0, 0.5, 0);
        AddMovementInput(Direction, Value);

        CharacterState = (Value > 0) ? EMainCharacterState::Right : EMainCharacterState::Left;
        LastMoveDirection = (CharacterState == EMainCharacterState::Right) ? EMainCharacterState::IdleRight : EMainCharacterState::IdleLeft;

        MainCharacterSpriteComponent->UpdateSprite(CharacterState);
    }
    // else if(Value == 0.0f && (Controller == nullptr) && (!bIsDead))
    // {
    //     MainCharacterSpriteComponent->UpdateSprite(LastMoveDirection);
    // }
}

// When the character dies
bool AMainPaperCharacter::Die()
{
    if(Health <= 0.0f)
    {
        bIsDead = true;
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
    return bIsDead;
}

