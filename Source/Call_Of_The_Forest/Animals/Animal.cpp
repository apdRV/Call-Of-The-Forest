// Fill out your copyright notice in the Description page of Project Settings.


#include "Animal.h"

AAnimal::AAnimal(){
    PrimaryActorTick.bCanEverTick = true;

    Speed = 0.05f;
    Health = 100.0f;
    bIsDead = false;
    bIsAttacking = false;
    Active = false;

    AnimalState = EAnimalState::IdleRightUp;
    LastAnimalState = EAnimalState::IdleRightUp;

	GetCapsuleComponent()->InitCapsuleSize(10.0f, 10.0f);
    GetCapsuleComponent()->CanCharacterStepUpOn = ECB_No;
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);
    GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Overlap);

    // Default sprite component properties
    GetSprite()->SetRelativeRotation(FRotator(0.0f, 90.0f, -90.0f));
    GetSprite()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

    AnimalFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("AnimalFlipbookComponent"));
    AnimalFlipbookComponent->SetupAttachment(RootComponent);
    SetupOwner(GetSprite());
    GetSprite()->CanCharacterStepUpOn = ECB_No;
    GetSprite()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    GetSprite()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    GetSprite()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    GetSprite()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
    GetSprite()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

    World = AStaticWorld::GetStaticWorld();
}

void AAnimal::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent); // может быть проблема чекнуть !!!!!
    PlayerInputComponent->BindAxis("MoveForwardBackward", this, &AAnimal::MoveForwardBackward);
    PlayerInputComponent->BindAxis("MoveRightLeft", this, &AAnimal::MoveRightLeft);
}

void AAnimal::Tick(float DeltaTime){
    Super::Tick(DeltaTime);
}

void AAnimal::SetupOwner(UPaperFlipbookComponent *m_owner)
{
    AnimalFlipbookComponent = m_owner;
}

void AAnimal::BeginPlay(){
    Super::BeginPlay();
}

void AAnimal::MoveRightLeft(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f) && (!bIsDead))
    {
        const FVector Direction = FVector(0, 0.05f, 0);
        AddMovementInput(Direction, Value);

        AnimalState = (Value > 0) ? EAnimalState::RightUp : EAnimalState::LeftDown;
        LastAnimalState = (AnimalState == EAnimalState::RightUp) ? EAnimalState::IdleRightUp : EAnimalState::IdleLeftDown;
    }
}

void AAnimal::MoveForwardBackward(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f) && (!bIsDead))
    {
        const FVector Direction = FVector(0.05f, 0, 0);
        AddMovementInput(Direction, Value);

        AnimalState = (Value > 0) ? EAnimalState::RightUp : EAnimalState::LeftDown;
        LastAnimalState = (AnimalState == EAnimalState::RightUp) ? EAnimalState::IdleRightUp : EAnimalState::IdleLeftDown;
    }
}

void AAnimal::UpdateAnimalSprite()
{
}

bool AAnimal::GetActive()
{
    return Active;
}

void AAnimal::SetActive(bool Value)
{
    Active = Value;
}


void AAnimal::Die()
{
}


