// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPaperCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

AMainPaperCharacter::AMainPaperCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

    // GetSprite()->SetupAttachment(RootComponent);


    //SpringArm
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeRotation(FRotator(-60.0f, -90.0f, -30.0f));
    CameraBoom->TargetArmLength = 100.f; // расстояние от камеры до игрока
    CameraBoom->bInheritPitch = false;
    CameraBoom->bInheritYaw = false;
    CameraBoom->bInheritRoll = false;


    //Camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    FollowCamera->SetupAttachment(CameraBoom);
    FollowCamera->bUsePawnControlRotation = false;

    // Default capsule component properties
	GetCapsuleComponent()->InitCapsuleSize(5.0f, 5.0f);

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

    PlayerInputComponent->BindAxis("MoveForward", this, &AMainPaperCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AMainPaperCharacter::MoveRight);
}

void AMainPaperCharacter::MoveForward(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        const FVector Direction = FVector(1, 0, 0);
        AddMovementInput(Direction, Value);
    }
}

void AMainPaperCharacter::MoveRight(float Value)
{
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
