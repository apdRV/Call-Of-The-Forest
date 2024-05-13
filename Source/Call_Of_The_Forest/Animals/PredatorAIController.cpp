// Fill out your copyright notice in the Description page of Project Settings.


#include "PredatorAIController.h"

APredatorAIController::APredatorAIController()
{
    PrimaryActorTick.bCanEverTick = true;
    World = AStaticWorld::GetStaticWorld();
    m_Predator = nullptr;
    wait_time = 0;
}

void APredatorAIController::BeginPlay()
{
    Super::BeginPlay();
    NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
}

void APredatorAIController::Tick(float Deltatime)
{
    Super::Tick(Deltatime);
    if(m_Predator != nullptr && wait_time > 100.0f && m_Predator->GetbIsActive()){
        RandomMove();
        wait_time = 0;
        UE_LOG(LogTemp, Warning, TEXT("Call Random Move"));
    }
    wait_time = (wait_time > 100.0f) ? wait_time : wait_time + 1;
}

void APredatorAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    m_Predator = dynamic_cast<APredator*>(InPawn);
    if(m_Predator == nullptr){
        UE_LOG(LogTemp, Warning, TEXT("Predator is null"));
    }
}

void APredatorAIController::RandomMove()
{
    if(m_Predator == nullptr){
        UE_LOG(LogTemp, Warning, TEXT("Predator is null"));
        return;
    }

    NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
    if(NavArea == nullptr){
        UE_LOG(LogTemp, Warning, TEXT("NavArea is null"));
        return;
    }

    FNavLocation NavLocation;
    bool bLocationValid = NavArea->GetRandomReachablePointInRadius(m_Predator->GetActorLocation(), 300.0f, NavLocation);
    if(bLocationValid){
        MoveToLocation(NavLocation.Location);
    }
}

void APredatorAIController::GenerateRandomLocation()
{
    FNavLocation Location{};
    if(m_Predator != nullptr){
        NavArea->GetRandomReachablePointInRadius(m_Predator->GetActorLocation(), 200.0f, Location);
    }
    RandomLocation = Location.Location;
}

void APredatorAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);
}