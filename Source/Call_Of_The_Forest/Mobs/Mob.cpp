// Fill out your copyright notice in the Description page of Project Settings.


#include "Mob.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/CapsuleComponent.h"

AMob::AMob()
{
    PrimaryActorTick.bCanEverTick = true;

    // Set spawn state
    bIsMoving = false;
    bIsDead = false;
    MobState = EMobState::IdleRightUp;
    LastMobState = EMobState::IdleRightUp;

    Health = 100.0f;
    MaxHealth = 100.0f;
    BaseDamage = 10.0f;


    //устанавливаем наш AIController
    AIControllerClass = AMobsAIController::StaticClass();

    // устанавливаем behaviourtree
    static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/AI_Mob.AI_Mob'"));
    if (BTObject.Succeeded())
    {
        Tree = BTObject.Object;
    }

    // Default capsule component properties
	GetCapsuleComponent()->InitCapsuleSize(10.0f, 10.0f);

    // Default sprite component properties
    GetSprite()->SetRelativeRotation(FRotator(0.0f, 90.0f, -90.0f));
    GetSprite()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
    // SetActorScale3D(FVector(0.75, 1.5, 15));

    MobSpriteComponent = CreateDefaultSubobject<UMobSpriteComponent>(TEXT("MobSpriteComponent"));
    MobSpriteComponent->SetupAttachment(RootComponent);
    MobSpriteComponent->SetupOwner(GetSprite());
    MobSpriteComponent->UpdateSprite(MobState);
}

void AMob::Tick(float Deltatime)
{
    Super::Tick(Deltatime);
    UpdateMobSprite();
}

void AMob::BeginPlay()
{

    //устанавливаем AiController
    AAIController* AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass);

    if (AIController)
    {
        AIController->Possess(this);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController not found"));
    }

}

UBehaviorTree* AMob::GetBehaviourTree() const
{
    return Tree;
}

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