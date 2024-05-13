
// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPaperCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "../Mobs/Mob.h"
#include "Components/CapsuleComponent.h"

AMainPaperCharacter::AMainPaperCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

    // Default character properties
	bIsMoving = false;
    bIsDead = false;
    bIsAttacking = 0;
    Health = 100.0f;
    CharacterState = EMainCharacterState::IdleDown;
    LastMoveDirection = EMainCharacterState::IdleDown;

    //SpringArm
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeRotation(FRotator(-90.0f, 180.0f, 180.0f));
    CameraBoom->TargetArmLength = 200.f; // расстояние от камеры до игрока
    CameraBoom->bInheritPitch = false;
    CameraBoom->bInheritYaw = false;
    CameraBoom->bInheritRoll = false;


    //Camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    FollowCamera->SetupAttachment(CameraBoom);
    FollowCamera->bUsePawnControlRotation = false;

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
}

// Called every frame
void AMainPaperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    UpdateCharacterSprite();
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

    PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMainPaperCharacter::Attack);
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
    bIsAttacking = 20;
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
    World->PlayerAttack(GetActorLocation(), CharacterState);
    // CODE FOR ATTACKING
}

void AMainPaperCharacter::UpdateCharacterSprite()
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
        CharacterState = LastMoveDirection;
    }
    MainCharacterSpriteComponent->UpdateSprite(CharacterState);

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
void AMainPaperCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
    AMob* Mob = dynamic_cast<AMob*>(OtherActor);
    if (Mob != nullptr)
    {
        Mob->SetTriggered(true);
        OverlappingActors.Add(OtherActor);
    }
    AAnimal* Animal = dynamic_cast<AAnimal*>(OtherActor);
    if(Animal != nullptr){
        Animal->SetbIsActive(true);
        OverlappingActors.Add(OtherActor);
    }
    APredator* Predator = dynamic_cast<APredator*>(OtherActor);
    if(Predator != nullptr){
        Predator->SetbIsActive(true);
        OverlappingActors.Add(OtherActor);
    }
}

void AMainPaperCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    AMob* Mob = dynamic_cast<AMob*>(OtherActor);
    if(Mob != nullptr){
        Mob->SetTriggered(false);
    }
    AAnimal* Animal = dynamic_cast<AAnimal*>(OtherActor);
    if(Animal != nullptr){
        Animal->SetbIsActive(false);
    }
    APredator* Predator = dynamic_cast<APredator*>(OtherActor);
    if(Predator != nullptr){
        Predator->SetbIsActive(false);
    }
    OverlappingActors.Remove(OtherActor);
}

