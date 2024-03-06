// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPaperCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"

AMainPaperCharacter::AMainPaperCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

    // GetSprite()->SetupAttachment(RootComponent);

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

    //Sprite
    DefaultSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("Spawn_sprite"));
    ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> MainCharacterAsset(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/SpawnSprite.SpawnSprite'"));
    DefaultSprite->SetFlipbook(MainCharacterAsset.Get());
    DefaultSprite->SetupAttachment(GetCapsuleComponent());
    DefaultSprite->SetRelativeRotation(FRotator(0.0f, 90.0f, -90.0f));
	DefaultSprite->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

	bIsMoving = false;
    bIsDead = false;
    Health = 100.0f;
}

// Called every frame
void AMainPaperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainPaperCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AMainPaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForwardBackward", this, &AMainPaperCharacter::MoveForwardBackward);
    PlayerInputComponent->BindAxis("MoveRightLeft", this, &AMainPaperCharacter::MoveRightLeft);
}

// When W or S are pressed
void AMainPaperCharacter::MoveForwardBackward(float Value)
{
    // FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxes(EAxis::X);
    // AddMovementInput(Direction, Value);
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        const FVector Direction = FVector(1, 0, 0);
        AddMovementInput(Direction, Value);
    }
}

// When A or D keys are pressed
void AMainPaperCharacter::MoveRightLeft(float Value)
{
    // FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxes(EAxis::Y);
    // AddMovementInput(Direction, Value);

    if ((Controller != nullptr) && (Value != 0.0f))
    {
        const FVector Direction = FVector(0, 1, 0);
        AddMovementInput(Direction, Value);
    }
}

bool AMainPaperCharacter::Die()
{
    if(Health <= 0.0f)
    {
        bIsDead = true;
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
    return bIsDead;
}
