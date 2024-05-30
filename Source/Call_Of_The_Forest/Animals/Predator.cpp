// Fill out your copyright notice in the Description page of Project Settings.


#include "Predator.h"

APredator::APredator()
{
    PrimaryActorTick.bCanEverTick = true;

    // Default Properties
    bSpeed = 60.0f;
    bHealth = 100.0f;
    bDamage = 5.0f;
    bIsDead = false;
    bIsAttacking = false;
    bIsTriggered = false;
    bIsActive = false;
    bIsDestroyed = false;

    //Walking Radius
    bRadius = 400.0f;

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

void APredator::Attacked(float Value)
{
    bHealth-=Value;
    bIsTriggered = true;
    SetbSpeed(100.0f);
    if(bHealth <= 0.0f)
    {
        Die();
    }
}

void APredator::SetAttackAnimation()
{
    bIsAttacking = true;
    if(PredatorState == EPredatorState::IdleLeftDown || PredatorState == EPredatorState::LeftDown)
    {
        PredatorState = EPredatorState::AttackingLeftDown;
    }
    else if(PredatorState == EPredatorState::IdleRightUp || PredatorState == EPredatorState::RightUp)
    {
        PredatorState = EPredatorState::AttackingRightUp;
    }
    UpdatePredatorSprite();
    GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &APredator::EndAttackAnimation, 0.6f, false);
}

void APredator::EndAttackAnimation()
{
    PredatorState = LastPredatorState;
    bIsAttacking = false;
    UpdatePredatorSprite();

}

void APredator::UpdatePredatorState()
{
    if(bIsAttacking)
    {
        return;
    }

    FVector Velocity = GetVelocity();

    if(PredatorState == EPredatorState::DieRightUp || PredatorState == EPredatorState::DieLeftDown)
    {
        LastPredatorState = (PredatorState == EPredatorState::DieLeftDown) ? EPredatorState::DieLeftDown : EPredatorState::DieRightUp;
        PredatorState = LastPredatorState;
        return;
    }

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

void APredator::SetupOwner(UPaperFlipbookComponent* m_owner)
{
    PredatorFlipbookComponent = m_owner;
}

void APredator::Die()
{
}

float APredator::GetbDamage()
{
    return bDamage;
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

bool APredator::GetbIsDead()
{
    return bIsDead;
}

float APredator::GetbRadius()
{
    return bRadius;
}

void APredator::SetbRadius(float Value)
{
    bRadius = Value;
}

void APredator::SetbSpeed(float Value)
{
    bSpeed = Value;
    GetCharacterMovement()->MaxWalkSpeed = bSpeed;
}

EPredatorState APredator::GetPredatorState()
{
    return PredatorState;
}

bool APredator::GetbIsDestroyed()
{
    return bIsDestroyed;
}

void APredator::SetbIsDestroyed(bool Value)
{
    bIsDestroyed = Value;
}

void APredator::SetPredatorState(EPredatorState NewState)
{
    PredatorState = NewState;
}

void APredator::SetPredatorLastState(EPredatorState NewState)
{
    LastPredatorState = NewState;
}
