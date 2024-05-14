// Fill out your copyright notice in the Description page of Project Settings.


#include "Predator.h"

APredator::APredator()
{
    PrimaryActorTick.bCanEverTick = true;

    // Default Properties
    Speed = 60.0f;
    Health = 100.0f;
    Damage = 20.0f;
    bIsDead = false;
    bIsAttacking = false;
    bIsTriggered = false;
    bIsActive = false;

    //Default State
    PredatorState = EPredatorState::IdleRightUp;
    LastPredatorState = EPredatorState::IdleRightUp;

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

    PredatorFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PredatorFlipbookComponent"));
    PredatorFlipbookComponent->SetupAttachment(RootComponent);
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

void APredator::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APredator::BeginPlay()
{
    Super::BeginPlay();
}

void APredator::UpdatePredatorSprite()
{

}

void APredator::SetupOwner(UPaperFlipbookComponent* m_owner)
{
    PredatorFlipbookComponent = m_owner;
}

void APredator::UpdatePredatorState()
{
    FVector Velocity = GetVelocity();

    if (Velocity.SizeSquared() > 0.0f)
    {
        PredatorState = (Velocity.Y > 0.0f) ? EPredatorState::RightUp : EPredatorState::LeftDown;
        LastPredatorState = (PredatorState == EPredatorState::RightUp) ? EPredatorState::IdleRightUp : EPredatorState::IdleLeftDown;
    }
    else
    {
        PredatorState = LastPredatorState;
    }
    UpdatePredatorSprite();
}

void APredator::Die()
{
}

bool APredator::GetbIsActive()
{
    return bIsActive;
}

void APredator::SetbIsActive(bool Value)
{
    bIsActive = Value;
}

bool APredator::GetbIsTriggered()
{
    return bIsTriggered;
}

void APredator::SetbIsTriggered(bool Value)
{
    bIsTriggered = Value;
}