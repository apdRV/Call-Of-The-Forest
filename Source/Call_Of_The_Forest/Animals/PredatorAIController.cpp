// Fill out your copyright notice in the Description page of Project Settings.


#include "PredatorAIController.h"

APredatorAIController::APredatorAIController()
{
    PrimaryActorTick.bCanEverTick = true;
    World = AStaticWorld::GetStaticWorld();
    bPredator = nullptr;
    bWaitTime = 3.0f;
    bCanMove = true;
    SearchRadius = 100.0f;
    bCanAttack = true;
    bAttackInterval = 1.0f;
}

void APredatorAIController::BeginPlay()
{
    Super::BeginPlay();
    NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
}

void APredatorAIController::Tick(float Deltatime)
{
    Super::Tick(Deltatime);
    if(bPredator != nullptr && bCanMove && bPredator->GetbIsActive() && !bPredator->GetbIsTriggered() && !bPredator->GetbIsDead()){
        RandomMove();
        UE_LOG(LogTemp, Warning, TEXT("Call Random Move"));
    }
    else if(bPredator != nullptr && bPredator->GetbIsTriggered() && !bPredator->GetbIsDead())
    {
        MoveToTarget();
        TriggerAttack();
    }
}

void APredatorAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    bPredator = dynamic_cast<APredator*>(InPawn);
    if(bPredator == nullptr){
        UE_LOG(LogTemp, Warning, TEXT("Predator is null"));
    }
}

void APredatorAIController::RandomMove()
{
    if(bPredator == nullptr){
        UE_LOG(LogTemp, Warning, TEXT("Predator is null"));
        return;
    }

    NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
    if(NavArea == nullptr){
        UE_LOG(LogTemp, Warning, TEXT("NavArea is null"));
        return;
    }

    FNavLocation NavLocation;
    SearchRadius = bPredator->GetbRadius();
    bool bLocationValid = NavArea->GetRandomReachablePointInRadius(bPredator->GetActorLocation(), SearchRadius, NavLocation);
    if(bLocationValid){
        MoveToLocation(NavLocation.Location);
        bCanMove = false;
        GetWorldTimerManager().SetTimer(TimerHandle, this, &APredatorAIController::ResetbCanMove, bWaitTime, false);
    }
}

void APredatorAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);
}

AMainPaperCharacter* APredatorAIController::FindTarget()
{
    AMainPaperCharacter* NearestPlayer;
    FVector MobLocation = bPredator->GetActorLocation();
    FVector NearestActorLocation;
    AMainPaperCharacter* NearestCharacter = nullptr;
    float NearestDistance;
    std::vector<AActor*> copy_array_of_main_characters = World->GetActor("MainCharacter");
    if(copy_array_of_main_characters.size() == 0){
        UE_LOG(LogTemp, Warning, TEXT("No_main_characters_in_area"));
        return NearestCharacter;
    }
    else {
        NearestActorLocation = copy_array_of_main_characters[0]->GetActorLocation();
        NearestDistance = FVector::DistSquared(NearestActorLocation, MobLocation);
        NearestCharacter = dynamic_cast<AMainPaperCharacter*>(copy_array_of_main_characters[0]);
    }
    for(int i=0;i< copy_array_of_main_characters.size();i++){
        FVector CurrentActorLocation = copy_array_of_main_characters[i]->GetActorLocation();
        float Distance = FVector::DistSquared(CurrentActorLocation, MobLocation);
        if(Distance < NearestDistance && i % 2 == 0){
            NearestDistance = Distance;
            NearestActorLocation = CurrentActorLocation;
            NearestCharacter = dynamic_cast<AMainPaperCharacter*>(copy_array_of_main_characters[i]);
        }
    }
    return NearestCharacter;
}

void APredatorAIController::MoveToTarget()
{
    if(bTargetMainCharacter == nullptr){
        bTargetMainCharacter = FindTarget();
    }
    if(bTargetMainCharacter != nullptr){
        NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
        MoveToActor(bTargetMainCharacter, 2.0f);
        
    } else {
        UE_LOG(LogTemp, Warning, TEXT("No_target_found"));
    }
}

void APredatorAIController::TriggerAttack()
{
    if(bCanAttack)
    {
        if(bTargetMainCharacter == nullptr)
        {
            bTargetMainCharacter = FindTarget();
        }
        if(bTargetMainCharacter != nullptr)
        {
            if(bTargetMainCharacter->GetActorLocation().Y - bPredator->GetActorLocation().Y < 0.0f)
            {
                bPredator->SetPredatorState(EPredatorState::IdleLeftDown);
                bPredator->SetPredatorLastState(EPredatorState::IdleLeftDown);
            }
            else{
                bPredator->SetPredatorState(EPredatorState::IdleRightUp);
                bPredator->SetPredatorLastState(EPredatorState::IdleRightUp);
            }
            World->PredatorIsAttacking(bTargetMainCharacter, bPredator);
            bCanAttack = false;
            GetWorldTimerManager().SetTimer(TimerHandle, this, &APredatorAIController::ResetAttack, bAttackInterval, false);
        }

    }
}

void APredatorAIController::ResetAttack()
{
    bCanAttack = true;
}

void APredatorAIController::ResetbCanMove()
{
    bCanMove = true;
}