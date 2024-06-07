// Fill out your copyright notice in the Description page of Project Settings.


#include "Mob.h"
#include "BehaviorTree/BehaviorTree.h"
#include <vector>
#include "../World/StaticWorld.h"
#include "../Character/MainPaperCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Components/CapsuleComponent.h"

AMob::AMob()
{
    PrimaryActorTick.bCanEverTick = true;

    // Set spawn state
    bIsMoving = false;
    bIsDead = false;
    bIsAttacking = false;
    MobState = EMobState::IdleRightUp;
    LastMobState = EMobState::IdleRightUp;

    //for server
    bReplicates = true;

    Health = 100.0f;
    MaxHealth = 100.0f;
    BaseDamage = 5.0f;
    Speed = 40.0f;
    bIsTriggered = false;
    bIsDestroyed = false;
    bRadius = 100.0f;



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

    MobFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("MobSpriteComponent"));
    MobFlipbookComponent->SetupAttachment(RootComponent);
    SetupOwner(GetSprite());
    GetSprite()->CanCharacterStepUpOn = ECB_No;
    GetSprite()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    GetSprite()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    GetSprite()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    GetSprite()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
    GetSprite()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

    //Properties for correct movement by AIController
    GetCharacterMovement()->MaxWalkSpeed = Speed;
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
    if (bIsAttacking) {
        SetAttackAnimation();
    }
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

void AMob::UpdateMobState()
{
    if(bIsAttacking)
    {
        return;
    }
    
    FVector Velocity = GetVelocity();
    
    if(MobState == EMobState::DieLeftDown || MobState == EMobState::DieRightUp)
    {
        LastMobState = (MobState == EMobState::DieLeftDown) ? EMobState::DieLeftDown : EMobState::DieRightUp;
        MobState = LastMobState;
        return;
    }

    else if (Velocity.SizeSquared() > 0.0f)
    {
        MobState = (Velocity.Y > 0.0f) ? EMobState::RightUp : EMobState::LeftDown;
        LastMobState = (MobState == EMobState::RightUp) ? EMobState::IdleRightUp : EMobState::IdleLeftDown;
    }
    else
    {
        MobState = LastMobState;
    }
    UpdateMobSprite();
}

void AMob::SetAttack()
{
    bIsAttacking = true;
}

void AMob::SetAttackAnimation()
{
    if(MobState == EMobState::IdleLeftDown || MobState == EMobState::LeftDown)
    {
        MobState = EMobState::AttackLeftDown;
    }
    else if(MobState == EMobState::IdleRightUp || MobState == EMobState::RightUp)
    {
        MobState = EMobState::AttackRightUp;
    }
    UpdateMobSprite();
    GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AMob::EndAttackAnimation, 0.8f, false);
}

void AMob::EndAttackAnimation()
{
    MobState = LastMobState;
    bIsAttacking = false;
    UpdateMobSprite();
}

void AMob::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AMob, MobState);
    DOREPLIFETIME(AMob, LastMobState);
	DOREPLIFETIME(AMob, bIsDead);
	DOREPLIFETIME(AMob, BaseDamage);
    DOREPLIFETIME(AMob, Health);
    DOREPLIFETIME(AMob, bIsAttacking);
}

void AMob::Attacked(float Value)
{
    Health-=Value;
    bIsTriggered = true;
    if(Health <= 0.0f)
    {
        Die();
    }
}

void AMob::Die()
{
    if(Health <= 0.0f)
    {
        bIsDead = true;
        MobState = (LastMobState == EMobState::IdleLeftDown || LastMobState == EMobState::LeftDown || LastMobState == EMobState::AttackLeftDown) ? EMobState::DieLeftDown : EMobState::DieRightUp;
        SetMobSprite(MobState);
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

void AMob::SetMobSprite(EMobState NewMobState)
{
    
}

void AMob::SetupOwner(UPaperFlipbookComponent *m_owner)
{
    MobFlipbookComponent = m_owner;
}

bool AMob::GetbIsTriggered()
{
    return bIsTriggered;
}

void AMob::SetbIsTriggered(bool Value)
{
    bIsTriggered = Value;
}

bool AMob::GetbIsDead()
{
    return bIsDead;
}

void AMob::SetSpeed(float Value)
{
    Speed = Value;
    GetCharacterMovement()->MaxWalkSpeed = Speed;
}

float AMob::GetRadius()
{
    return bRadius;
}

void AMob::SetRadius(float Value)
{
    bRadius = Value;
}

float AMob::GetSpeed()
{
    return Speed;
}

EMobState AMob::GetMobState(){
    return MobState;
}

EMobState AMob::GetLastMobState(){
    return LastMobState;
}

void AMob::SetMobState(EMobState NewState){
    MobState = NewState;
}

void AMob::SetLastMobState(EMobState NewState)
{
    LastMobState = NewState;
}

void AMob::UpdateMobSprite()
{

}

float AMob::GetBaseDamage()
{
    return BaseDamage;
}

bool AMob::GetbIsDestroyed()
{
    return bIsDestroyed;
}

void AMob::SetbIsDestroyed(bool Value)
{
    bIsDestroyed = Value;
}
