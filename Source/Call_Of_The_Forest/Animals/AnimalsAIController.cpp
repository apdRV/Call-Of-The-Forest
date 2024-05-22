// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalsAIController.h"

AAnimalsAIController::AAnimalsAIController()
{
    PrimaryActorTick.bCanEverTick = true;
    World = AStaticWorld::GetStaticWorld();
    bAnimal = nullptr;
    bWaitTime = 3.0f;
    bCanMove = true;
    bSearchRadius = 100.0f;
}

void AAnimalsAIController::BeginPlay()
{
    Super::BeginPlay();
    NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
}

void AAnimalsAIController::Tick(float Delta)
{
    Super::Tick(Delta);
    if(bAnimal != nullptr && bCanMove && bAnimal->GetbIsActive() && !bAnimal->GetbIsDead()){
        RandomMove();
        // UE_LOG(LogTemp, Warning, TEXT("Call Random Move"));
    }
}

void AAnimalsAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    bAnimal = dynamic_cast<AAnimal*>(InPawn);
    bSearchRadius = bAnimal->GetbRadius();
    if(bAnimal == nullptr){
        UE_LOG(LogTemp, Warning, TEXT("Animal is null"));
    }
}

void AAnimalsAIController::RandomMove()
{
    if(bAnimal == nullptr){
        UE_LOG(LogTemp, Warning, TEXT("Animal is null"));
        return;
    }

    NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
    if(NavArea == nullptr){
        UE_LOG(LogTemp, Warning, TEXT("NavArea is null"));
        return;
    }

    FNavLocation NavLocation;
    bSearchRadius = bAnimal->GetbRadius();
    bool bLocationValid = NavArea->GetRandomReachablePointInRadius(bAnimal->GetActorLocation(), bSearchRadius, NavLocation);
    if(bLocationValid){
        MoveToLocation(NavLocation.Location);
        bCanMove = false;
        GetWorldTimerManager().SetTimer(TimerHandle, this, &AAnimalsAIController::ResetbCanMove, bWaitTime, false);
    }
}

void AAnimalsAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);
}

void AAnimalsAIController::ResetbCanMove()
{
    bCanMove = true;
}
