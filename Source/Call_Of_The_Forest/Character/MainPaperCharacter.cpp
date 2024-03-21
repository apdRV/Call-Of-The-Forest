// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPaperCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Resources/ResourceBaseClass/ResourceBase.h"
#include "../Inventory/InventoryItem.h"
#include "../Inventory/InventoryController.h"

AMainPaperCharacter::AMainPaperCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

    // Default character properties
	bIsMoving = false;
    bIsDead = false;
    bIsAttacking = 0;
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
    UpdateCharacterSprite();
    CheckForInteractables();
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

    //can make action, but 
    PlayerInputComponent->BindAxis("PickUpItem", this, &AMainPaperCharacter::PickUpItem);

    PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMainPaperCharacter::Attack);
}

void AMainPaperCharacter::PickUpItem(float Value)
{
    //code for implementing the pick up item
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

    }
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

    }
}

void AMainPaperCharacter::Attack()
{
    bIsAttacking = 20;
    //Change the character state to attack
    if(CharacterState == EMainCharacterState::IdleDown || CharacterState == EMainCharacterState::Down)
    {
        LastMoveDirection = EMainCharacterState::IdleDown;
        CharacterState = EMainCharacterState::AttackDown;
    }
    else if(CharacterState == EMainCharacterState::IdleUp || CharacterState == EMainCharacterState::Up)
    {
        LastMoveDirection = EMainCharacterState::IdleUp;
        CharacterState = EMainCharacterState::AttackUp;
    }
    else if(CharacterState == EMainCharacterState::IdleRight || CharacterState == EMainCharacterState::Right)
    {
        LastMoveDirection = EMainCharacterState::IdleRight;
        CharacterState = EMainCharacterState::AttackRight;
    }
    else if(CharacterState == EMainCharacterState::IdleLeft || CharacterState == EMainCharacterState::Left)
    {
        LastMoveDirection = EMainCharacterState::IdleLeft;
        CharacterState = EMainCharacterState::AttackLeft;
    }
    // CODE FOR ATTACKING
}

void AMainPaperCharacter::UpdateCharacterSprite()
{
    if((bIsAttacking != 0) && (!bIsDead))
    {
        bIsAttacking--;
    }
    else if(Health <= 0.0f){
        Die();
    }
    else if(GetVelocity().IsNearlyZero() && (!bIsDead))
    {
        CharacterState = LastMoveDirection;
    }
    MainCharacterSpriteComponent->UpdateSprite(CharacterState);

}

// When the character dies
void AMainPaperCharacter::Die()
{
    if(Health <= 0.0f)
    {
        bIsDead = true;
        CharacterState = (LastMoveDirection == EMainCharacterState::IdleLeft) ? EMainCharacterState::DieLeft : EMainCharacterState::DieRight;
        MainCharacterSpriteComponent->UpdateSprite(CharacterState);
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        EndPlay(EEndPlayReason::Destroyed);
    }
}

void AMainPaperCharacter::CheckForInteractables()
{
    FHitResult HitResult;
    int32 Range = 100;
    FVector StartTrace = FollowCamera->GetComponentLocation();
    FVector EndTrace = (FollowCamera->GetForwardVector() * Range) + StartTrace;

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    AInventoryController* IController = Cast<AInventoryController>(GetController());

    if (IController){
        if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, QueryParams))
        {
            // Cast the actor to AInteractable
            AResourceBase* Interactable = Cast<AResourceBase>(HitResult.GetActor());
            // If the cast is successful
            if (Interactable)
            {
                IController->CurrentInteractable = Interactable;
                return;
            }
        }

        IController->CurrentInteractable = nullptr;
    }
}

