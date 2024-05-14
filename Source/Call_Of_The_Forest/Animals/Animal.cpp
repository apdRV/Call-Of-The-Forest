// Fill out your copyright notice in the Description page of Project Settings.


#include "Animal.h"

AAnimal::AAnimal(){
    PrimaryActorTick.bCanEverTick = true;

    Speed = 0.05f;
    Health = 100.0f;
    bIsDead = false;
    bIsAttacking = false;
    bIsActive = false;

    AnimalState = EAnimalState::IdleRightUp;
    LastAnimalState = EAnimalState::IdleRightUp;

    // Default capsule component properties
	GetCapsuleComponent()->InitCapsuleSize(11.0f, 11.0f);
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

    //Properties for correct movement by AIController
    GetCharacterMovement()->bOrientRotationToMovement = false;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 0.f, 0.f);
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->bSnapToPlaneAtStart = true;
    GetCharacterMovement()->bIgnoreBaseRotation = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;
    
    World = AStaticWorld::GetStaticWorld();
}

void AAnimal::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AAnimal::BeginPlay()
{
    Super::BeginPlay();
}

void AAnimal::SetupOwner(UPaperFlipbookComponent *m_owner)
{
    AnimalFlipbookComponent = m_owner;
}


void AAnimal::UpdateAnimalSprite()
{
}

bool AAnimal::GetbIsActive()
{
    return bIsActive;
}

void AAnimal::SetbIsActive(bool Value)
{
    bIsActive = Value;
}

void AAnimal::Attacked(float Value)
{
    Health -= Value;
    if(Health <= 0.0f)
    {
        bIsDead = true;
        Die();
    }
}

void AAnimal::UpdateAnimalState()
{
    FVector Velocity = GetVelocity();

    if (Velocity.SizeSquared() > 0.0f)
    {
        AnimalState = (Velocity.Y > 0.0f) ? EAnimalState::RightUp : EAnimalState::LeftDown;
        LastAnimalState = (AnimalState == EAnimalState::RightUp) ? EAnimalState::IdleRightUp : EAnimalState::IdleLeftDown;
    }
    else
    {
        AnimalState = LastAnimalState;
    }
    UpdateAnimalSprite();
}

void AAnimal::Die()
{
}

bool AAnimal::GetbIsDead()
{
    return bIsDead;
}