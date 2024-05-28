
// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPaperCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Resources/ResourceBaseClass/ResourceBase.h"

AMainPaperCharacter::AMainPaperCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

    // Default character properties
	bIsMoving = false;
    bIsDead = false;
    bIsAttacking = false;
    Damage = 30.0f;
    Health = 100.0f;
    CharacterState = EMainCharacterState::IdleDown;
    LastMoveDirection = EMainCharacterState::IdleDown;

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

    MainCharacterSpriteComponent = CreateDefaultSubobject<UMainCharacterSpriteComponent>(TEXT("MainCharacterSpriteComponent"));
    MainCharacterSpriteComponent->SetupAttachment(RootComponent);
    MainCharacterSpriteComponent->SetupOwner(GetSprite());
    GetSprite()->CanCharacterStepUpOn = ECB_No;
    GetSprite()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    GetSprite()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    GetSprite()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    GetSprite()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
    GetSprite()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    MainCharacterSpriteComponent->UpdateSprite(CharacterState);

    //World properties
    World = AStaticWorld::GetStaticWorld();

    // Properties for Sphere
    TriggerRadius = 100.0f;
    SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
    SphereCollider->InitSphereRadius(TriggerRadius); // radius to trigger mobs
    SphereCollider->SetCollisionProfileName(TEXT("OverlapAll"));
    SphereCollider->SetupAttachment(RootComponent);

    SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AMainPaperCharacter::OnOverlapBegin);
    SphereCollider->OnComponentEndOverlap.AddDynamic(this, &AMainPaperCharacter::OnOverlapEnd);

    // InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
    // InteractionSphere->SetSphereRadius(20.f);
    // InteractionSphere->SetCollisionProfileName(TEXT("Trigger"));
    // InteractionSphere->SetupAttachment(RootComponent);

    // InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &AMainPaperCharacter::OnOverlapBegin);
}

// Called every frame
void AMainPaperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(!bIsDead){
        UpdateCharacterSprite();
    }
}

// Called when the game starts or when spawned
void AMainPaperCharacter::BeginPlay()
{
    Super::BeginPlay();
    if (World != nullptr) {
        World->AddActor("MainCharacter", this);
        UE_LOG(LogTemp, Warning, TEXT("Add MainCharacter"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("World is null"));
    }
}

// Called to bind functionality to input
void AMainPaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForwardBackward", this, &AMainPaperCharacter::MoveForwardBackward);
    PlayerInputComponent->BindAxis("MoveRightLeft", this, &AMainPaperCharacter::MoveRightLeft);

    //can make action, but 
    PlayerInputComponent->BindAxis("PickUpItem", this, &AMainPaperCharacter::PickUpItem);

    PlayerInputComponent->BindAction("EatMeat", IE_Pressed, this, &AMainPaperCharacter::EatMeat);

    PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMainPaperCharacter::Attack);

    PlayerInputComponent->BindAction("UpgradeSword", IE_Pressed, this, &AMainPaperCharacter::UpgradeSword);
}

void AMainPaperCharacter::PickUpItem(float Value)
{
    //code for implementing the pick up item
}

// When W/UP or S/DOWN are pressed
void AMainPaperCharacter::MoveForwardBackward(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f) && (!bIsDead))
    {
        const FVector Direction = FVector(0.5, 0, 0);
        AddMovementInput(Direction, Value);


        CharacterState = (Value > 0) ? EMainCharacterState::Up : EMainCharacterState::Down;
        LastMoveDirection = (CharacterState == EMainCharacterState::Up) ? EMainCharacterState::IdleUp : EMainCharacterState::IdleDown;

    }
}

// When A/LEFT or D/RIGHT keys are pressed
void AMainPaperCharacter::MoveRightLeft(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f) && (!bIsDead))
    {
        const FVector Direction = FVector(0, 0.5, 0);
        AddMovementInput(Direction, Value);

        CharacterState = (Value > 0) ? EMainCharacterState::Right : EMainCharacterState::Left;
        LastMoveDirection = (CharacterState == EMainCharacterState::Right) ? EMainCharacterState::IdleRight : EMainCharacterState::IdleLeft;

    }
}

void AMainPaperCharacter::Attack()
{
    SetAttackAnimation();
    if(World != nullptr)
    {
        World->PlayerAttack(GetActorLocation(), CharacterState, this);
    }
}

void AMainPaperCharacter::SetAttackAnimation()
{
    bIsAttacking = true;
    //Change the character state to attack
    if(CharacterState == EMainCharacterState::IdleDown || CharacterState == EMainCharacterState::Down)
    {
        LastMoveDirection = EMainCharacterState::IdleDown;
        CharacterState = EMainCharacterState::AttackDown;
    }
    else if(CharacterState == EMainCharacterState::IdleUp || CharacterState == EMainCharacterState::Up)
    {
        LastMoveDirection = EMainCharacterState::IdleUp;
        CharacterState = EMainCharacterState::AttackUp;
    }
    else if(CharacterState == EMainCharacterState::IdleRight || CharacterState == EMainCharacterState::Right)
    {
        LastMoveDirection = EMainCharacterState::IdleRight;
        CharacterState = EMainCharacterState::AttackRight;
    }
    else if(CharacterState == EMainCharacterState::IdleLeft || CharacterState == EMainCharacterState::Left)
    {
        LastMoveDirection = EMainCharacterState::IdleLeft;
        CharacterState = EMainCharacterState::AttackLeft;
    }
    if(!bIsDead)
    {
        MainCharacterSpriteComponent->UpdateSprite(CharacterState);
    }
    GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AMainPaperCharacter::EndAttackAnimation, 0.2f, false);
}

void AMainPaperCharacter::EndAttackAnimation()
{
    CharacterState = LastMoveDirection;
    bIsAttacking = false;
    UpdateCharacterSprite();

}

void AMainPaperCharacter::UpdateCharacterSprite()
{
    if((bIsAttacking) && (!bIsDead))
    {
        return;
    }
    else if(Health <= 0.0f){
        Die();
    }
    else if(GetVelocity().IsNearlyZero() && (!bIsDead))
    {
        CharacterState = LastMoveDirection;
    }
    MainCharacterSpriteComponent->UpdateSprite(CharacterState);

}

void AMainPaperCharacter::Attacked(float Value)
{
    Health-=Value;
    UE_LOG(LogTemp, Warning, TEXT("Called Attacked in MainPaperCharacter"));
    if(Health <= 0.0f)
    {
        Die();
    }
}

// When the character dies
void AMainPaperCharacter::Die()
{
    if(Health <= 0.0f)
    {
        bIsDead = true;
        CharacterState = (LastMoveDirection == EMainCharacterState::IdleLeft) ? EMainCharacterState::DieLeft : EMainCharacterState::DieRight;
        MainCharacterSpriteComponent->UpdateSprite(CharacterState);
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        EndPlay(EEndPlayReason::Destroyed);
    }
}

//funtion to deal with other actors
void AMainPaperCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(World != nullptr)
    {
        World->AddOverlappingActors(OtherActor);
    }

    // AResourceBase* Resource = Cast<AResourceBase>(OtherActor);
    // if(Resource)
    // {
    //     Resource->OnPickup(this);
    // }
}

void AMainPaperCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if(World != nullptr)
    {
        World->DeleteOverlappingActors(OtherActor);
    }

}

float AMainPaperCharacter::GetDamage()
{
    return Damage;
}

EMainCharacterState AMainPaperCharacter::GetCharacterState()
{
    return CharacterState;
}

bool AMainPaperCharacter::GetbIsDead()
{
    return bIsDead;
}

void AMainPaperCharacter::EatMeat(){
    if (MeatQuantity > 0){
        Health += 10.0f;
        if(Health > 100.0f){
            Health = 100.0f;
        }
        MeatQuantity--;
    }
}

void AMainPaperCharacter::UpgradeSword(){
    switch(SwordLevel)
    {
        case 0:
            if (WoodQuantity >= 100 && StoneQuantity >= 70){
                Damage += 5;
                SwordLevel = 1;
                WoodQuantity -= 100;
                StoneQuantity -= 70;
                break;
            }
        case 1:
            if (WoodQuantity >= 200 && StoneQuantity >= 140){
                Damage += 10;
                SwordLevel = 2;
                WoodQuantity -= 200;
                StoneQuantity -= 140;
                break;
            }
        case 2:
            if (WoodQuantity >= 300 && StoneQuantity >= 210){
                Damage += 15;
                SwordLevel = 3;
                WoodQuantity -= 300;
                StoneQuantity -= 210;
                break;
            }
        case 3:
            if (WoodQuantity >= 400 && StoneQuantity >= 280){
                Damage += 20;
                SwordLevel = 3;
                WoodQuantity -= 400;
                StoneQuantity -= 280;
                break;
            }
    }
}