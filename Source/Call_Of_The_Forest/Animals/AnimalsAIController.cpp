// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalsAIController.h"

AAnimalsAIController::AAnimalsAIController()
{
    PrimaryActorTick.bCanEverTick = true;
    World = AStaticWorld::GetStaticWorld();
    m_Animal = nullptr;
    wait_time = 0;
}

void AAnimalsAIController::BeginPlay()
{
    Super::BeginPlay();
    NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

}

void AAnimalsAIController::Tick(float Delta)
{
    Super::Tick(Delta);
    if(m_Animal != nullptr && wait_time > 100.0f && m_Animal->GetActive()){
        RandomMove();
        wait_time = 0;
        UE_LOG(LogTemp, Warning, TEXT("Call Random Move"));
    }
    wait_time = (wait_time > 100.0f) ? wait_time : wait_time + 1;
}

void AAnimalsAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    m_Animal = dynamic_cast<AAnimal*>(InPawn);
    if(m_Animal == nullptr){
        UE_LOG(LogTemp, Warning, TEXT("Animal is null"));
    }
}

void AAnimalsAIController::RandomMove()
{
    if(m_Animal == nullptr){
        UE_LOG(LogTemp, Warning, TEXT("Animal is null"));
        return;
    }

    NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
    if(NavArea == nullptr){
        UE_LOG(LogTemp, Warning, TEXT("NavArea is null"));
        return;
    }

    FNavLocation NavLocation;
    bool bLocationValid = NavArea->GetRandomReachablePointInRadius(m_Animal->GetActorLocation(), 300.0f, NavLocation);
    if(bLocationValid){
        MoveToLocation(NavLocation.Location);
    }
}

void AAnimalsAIController::GenerateRandomLocation()
{
    FNavLocation Location{};
    if(m_Animal != nullptr){
        NavArea->GetRandomReachablePointInRadius(m_Animal->GetActorLocation(), 200.0f, Location);
    }
    RandomLocation = Location.Location;
}

void AAnimalsAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);
}
