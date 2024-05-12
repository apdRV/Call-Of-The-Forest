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
    RandomMove();
}

void AAnimalsAIController::Tick(float Delta)
{
    Super::Tick(Delta);
    if(m_Animal != nullptr && wait_time > 50){
        RandomMove();
        wait_time = 0;
        UE_LOG(LogTemp, Warning, TEXT("Call Random Move"));
    }
    wait_time++;
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
        return;
    }
    GenerateRandomLocation();
    // while(FVector::Dist(m_Animal->GetActorLocation(), RandomLocation) < 10.0f){
    FVector CurrentLocation = m_Animal->GetActorLocation();
    FVector Direction = (RandomLocation - CurrentLocation).GetSafeNormal();
    // m_Animal->MoveForwardBackward(Direction.X);
    // m_Animal->MoveRightLeft(Direction.Y);
    m_Animal->MoveForwardBackward(1);
    m_Animal->MoveRightLeft(1);
    // }
	// if (/*IsValid(NavArea) &&*/ m_Animal)
	// {
    //     GenerateRandomLocation();
    //     FVector CurrentLocation = m_Animal->GetActorLocation();
    //     FVector Direction = (RandomLocation - CurrentLocation).GetSafeNormal();
    //     m_Animal->MoveForwardBackward(Direction.X);
    //     m_Animal->MoveRightLeft(Direction.Y);

    //     GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAnimalsAIController::RandomMove, 5.0f, false);
	// }
}

void AAnimalsAIController::GenerateRandomLocation()
{
    FNavLocation Location{};
    if(m_Animal != nullptr){
        NavArea->GetRandomReachablePointInRadius(m_Animal->GetActorLocation(), 200.0f, Location);
    }
    RandomLocation = Location.Location;
}
