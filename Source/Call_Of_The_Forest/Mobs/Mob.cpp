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
    Spead = 10.0f;

    // устанавливаем behaviourtree
    // static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/AI_Mob.AI_Mob'"));
    // if (BTObject.Succeeded())
    // {
    //     Tree = BTObject.Object;
    // }

    //AI Properties end




    // Default capsule component properties
	GetCapsuleComponent()->InitCapsuleSize(12.0f, 12.0f);

    // Default sprite component properties
    GetSprite()->SetRelativeRotation(FRotator(0.0f, 90.0f, -90.0f));
    GetSprite()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

    MobSpriteComponent = CreateDefaultSubobject<UMobFlipbookComponent>(TEXT("MobSpriteComponent"));
    MobSpriteComponent->SetupAttachment(RootComponent);
    MobSpriteComponent->SetupOwner(GetSprite());
    GetSprite()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetSprite()->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
    GetSprite()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    GetSprite()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
    GetSprite()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    GetSprite()->CanCharacterStepUpOn = ECB_No;
    MobSpriteComponent->UpdateSprite(MobState);

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

    //can make action, but 

    // PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMob::Attack);
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

// UBehaviorTree* AMob::GetBehaviourTree() const
// {
//     return Tree;
// }

void AMob::UpdateMobSprite()
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

