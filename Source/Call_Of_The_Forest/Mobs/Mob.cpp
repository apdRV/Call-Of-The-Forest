// Fill out your copyright notice in the Description page of Project Settings.


#include "Mob.h"

#include "BehaviorTree/BehaviorTree.h"
#include <vector>
#include "../World/StaticWorld.h"
#include "../Character/MainPaperCharacter.h"
#include "Components/CapsuleComponent.h"

AMob::AMob()
{
    PrimaryActorTick.bCanEverTick = true;

    // Set spawn state
    bIsMoving = false;
    bIsDead = false;
    bIsAttacking = 0;
    MobState = EMobState::IdleRightUp;
    LastMobState = EMobState::IdleRightUp;

    Health = 100.0f;
    MaxHealth = 100.0f;
    BaseDamage = 10.0f;
    Speed = 40.0f;
    triggered = false;



    // Default capsule component properties
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

    MobSpriteComponent = CreateDefaultSubobject<UMobFlipbookComponent>(TEXT("MobSpriteComponent"));
    MobSpriteComponent->SetupAttachment(RootComponent);
    MobSpriteComponent->SetupOwner(GetSprite());
    GetSprite()->CanCharacterStepUpOn = ECB_No;
    GetSprite()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    GetSprite()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    GetSprite()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    GetSprite()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
    GetSprite()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    MobSpriteComponent->UpdateSprite(MobState);

    //Properties for correct movement by AIController
    GetCharacterMovement()->MaxWalkSpeed = Speed;  // Adjust this value as needed
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

void AMob::Tick(float Deltatime)
{
    Super::Tick(Deltatime);
    UpdateMobSprite();
}

void AMob::BeginPlay()
{
    Super::BeginPlay();
    if (World != nullptr) {
        World->AddActor("Mob", this);
        UE_LOG(LogTemp, Warning, TEXT("World is not a null, added mob"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("World is null"));
    }

    UE_LOG(LogTemp, Warning, TEXT("SkeletonSpawned"));
}

void AMob::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent); // может быть проблема чекнуть !!!!!
    PlayerInputComponent->BindAxis("MoveForwardBackward", this, &AMob::MoveForwardBackward);
    PlayerInputComponent->BindAxis("MoveRightLeft", this, &AMob::MoveRightLeft);

    PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMob::Attack);
}


void AMob::MoveForwardBackward(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f) && (!bIsDead))
    {
        const FVector Direction = FVector(0.05, 0, 0);
        AddMovementInput(Direction, Value);

        MobState = (Value > 0) ? EMobState::RightUp : EMobState::LeftDown;
        LastMobState = (MobState == EMobState::RightUp) ? EMobState::IdleRightUp : EMobState::IdleLeftDown;
    }
}

void AMob::MoveRightLeft(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f) && (!bIsDead))
    {
        const FVector Direction = FVector(0, 0.05, 0);
        AddMovementInput(Direction, Value);

        MobState = (Value > 0) ? EMobState::RightUp : EMobState::LeftDown;
        LastMobState = (MobState == EMobState::RightUp) ? EMobState::IdleRightUp : EMobState::IdleLeftDown;
    }
}

void AMob::Attack()
{

}

void AMob::UpdateMobSprite()
{
    FVector Velocity = GetVelocity();

    if (Velocity.SizeSquared() > 0.0f)
    {
        MobState = (Velocity.Y > 0.0f) ? EMobState::RightUp : EMobState::LeftDown;
        LastMobState = (MobState == EMobState::RightUp) ? EMobState::IdleRightUp : EMobState::IdleLeftDown;
    }
    else
    {
        MobState = LastMobState;
    }
    MobSpriteComponent->UpdateSprite(MobState);
}

void AMob::Die()
{
    if(Health <= 0.0f)
    {
        bIsDead = true;
        MobState = (LastMobState == EMobState::IdleLeftDown) ? EMobState::DieLeftDown : EMobState::DieRightUp;
        MobSpriteComponent->UpdateSprite(MobState);

    }
}


bool AMob::GetTriggered()
{
    return triggered;
}

void AMob::SetTriggered(bool Value)
{
    triggered = Value;
}

