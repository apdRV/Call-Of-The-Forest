// Fill out your copyright notice in the Description page of Project Settings.


#include "Mob.h"

// #include "BehaviorTree/BehaviorTree.h"
#include <vector>
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



    //AI Properties begin
    //устанавливаем наш AIController
//    AIControllerClass = AMobsAIController::StaticClass();

    // устанавливаем behaviourtree
    // static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/AI_Mob.AI_Mob'"));
    // if (BTObject.Succeeded())
    // {
    //     Tree = BTObject.Object;
    // }

    //AI Properties end




    // Default capsule component properties
	GetCapsuleComponent()->InitCapsuleSize(10.0f, 10.0f);

    // Default sprite component properties
    GetSprite()->SetRelativeRotation(FRotator(0.0f, 90.0f, -90.0f));
    GetSprite()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

    MobSpriteComponent = CreateDefaultSubobject<UMobSpriteComponent>(TEXT("MobSpriteComponent"));
    MobSpriteComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    MobSpriteComponent->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
    MobSpriteComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    MobSpriteComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
    MobSpriteComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    MobSpriteComponent->CanCharacterStepUpOn = ECB_No;
    
    GetSprite()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetSprite()->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
    GetSprite()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    GetSprite()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
    GetSprite()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    GetSprite()->CanCharacterStepUpOn = ECB_No;

    MobSpriteComponent->SetupAttachment(RootComponent);
    MobSpriteComponent->SetupOwner(GetSprite());
    MobSpriteComponent->UpdateSprite(MobState);

    // World = AStaticWorld::GetStaticWorld();
    // World->AddActor("Mob", this);
}

void AMob::Tick(float Deltatime)
{
    Super::Tick(Deltatime);
    UpdateMobSprite();
    // if(Controller != nullptr){
    //     UE_LOG(LogTemp, Warning, TEXT("AIController found"));
    // }
}

void AMob::BeginPlay()
{
    Super::BeginPlay();
   // GetController()->SetAIControllerClass(AMobsAIController::StaticClass());

    //!!!!!! устанавливаем AiController МОГУТ БЫТЬ ПРОБЛЕМЫ!!!!!!!!
    AAIController* AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass);

    if (AIController)
    {
        AIController->Possess(this);
        UE_LOG(LogTemp, Warning, TEXT("AIController found"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController not found"));
    }

    UE_LOG(LogTemp, Warning, TEXT("SkeletonSpawned"));
}

void AMob::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent); // может быть проблема чекнуть !!!!!

    PlayerInputComponent->BindAxis("MoveForwardBackward", this, &AMob::MoveForwardBackward);
    PlayerInputComponent->BindAxis("MoveRightLeft", this, &AMob::MoveRightLeft);

    //can make action, but 
    PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMob::Attack);
}

void AMob::MoveForwardBackward(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f) && (!bIsDead))
    {
    //    UE_LOG(LogTemp, Warning, TEXT("Go_forward_backward"));
        const FVector Direction = FVector(0.05, 0, 0);
        AddMovementInput(Direction, Value);

        MobState = (Value > 0) ? EMobState::RightUp : EMobState::LeftDown;
        LastMobState = (MobState == EMobState::RightUp) ? EMobState::IdleRightUp : EMobState::IdleLeftDown;
    }
}

// When A/LEFT or D/RIGHT keys are pressed
void AMob::MoveRightLeft(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f) && (!bIsDead))
    {
        UE_LOG(LogTemp, Warning, TEXT("Go_right_left"));
        const FVector Direction = FVector(0, 0.2, 0);
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

// AMainPaperCharacter* AMob::FindTarget(){
//     AMainPaperCharacter* NearestPlayer;
//     FVector MobLocation = GetActorLocation();
//     FVector NearestActorLocation;
//     AMainPaperCharacter* NearestCharacter;
//     float NearestDistance;
//     std::vector<AActor*> copy_array_of_main_characters = World->GetActor("MainCharacter");
//     if(copy_array_of_main_characters.size() == 0){
//         UE_LOG(LogTemp, Warning, TEXT("No_main_characters_in_area"));
//     }
//     else{
//         NearestActorLocation = copy_array_of_main_characters[0]->GetActorLocation();
//         NearestDistance = FVector::DistSquared(NearestActorLocation, MobLocation);
//         NearestCharacter = Cast<AMainPaperCharacter>(copy_array_of_main_characters[0]);
//     }
//     for(auto &i : copy_array_of_main_characters){
//         FVector CurrentActorLocation = i->GetActorLocation();
//         float Distance = FVector::DistSquared(CurrentActorLocation, MobLocation);
//         if(Distance > NearestDistance){
//             NearestDistance = Distance;
//             NearestActorLocation = CurrentActorLocation;
//             NearestCharacter = Cast<AMainPaperCharacter>(i);
//         }
//     }
//     return NearestCharacter;
// }