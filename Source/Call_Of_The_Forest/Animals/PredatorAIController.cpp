// Fill out your copyright notice in the Description page of Project Settings.


#include "PredatorAIController.h"

APredatorAIController::APredatorAIController()
{
    PrimaryActorTick.bCanEverTick = true;
    World = AStaticWorld::GetStaticWorld();
    m_Predator = nullptr;
    wait_time = 0;
    SearchRadius = 100.0f;
    bCanAttack = true;
    AttackInterval = 1.0f;
}

void APredatorAIController::BeginPlay()
{
    Super::BeginPlay();
    NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
}

void APredatorAIController::Tick(float Deltatime)
{
    Super::Tick(Deltatime);
    if(m_Predator != nullptr && wait_time > 50.0f && m_Predator->GetbIsActive() && !m_Predator->GetbIsTriggered() && !m_Predator->GetbIsDead()){
        RandomMove();
        wait_time = 0;
        UE_LOG(LogTemp, Warning, TEXT("Call Random Move"));
    }
    else if(m_Predator != nullptr && m_Predator->GetbIsTriggered() && !m_Predator->GetbIsDead())
    {
        MoveToTarget();
        TriggerAttack();
    }
    wait_time = (wait_time > 50.0f) ? wait_time : wait_time + 1;
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
    SearchRadius = m_Predator->GetRadius();
    bool bLocationValid = NavArea->GetRandomReachablePointInRadius(m_Predator->GetActorLocation(), SearchRadius, NavLocation);
    if(bLocationValid){
        MoveToLocation(NavLocation.Location);
    }
}

void APredatorAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);
}

AMainPaperCharacter* APredatorAIController::FindTarget()
{
    AMainPaperCharacter* NearestPlayer;
    FVector MobLocation = m_Predator->GetActorLocation();
    FVector NearestActorLocation;
    AMainPaperCharacter* NearestCharacter = nullptr;
    float NearestDistance;
    std::vector<AActor*> copy_array_of_main_characters = World->GetActor("MainCharacter");
    if(copy_array_of_main_characters.size() == 0){
        UE_LOG(LogTemp, Warning, TEXT("No_main_characters_in_area"));
        return NearestCharacter;
    }
    else{
        NearestActorLocation = copy_array_of_main_characters[0]->GetActorLocation();
        NearestDistance = FVector::DistSquared(NearestActorLocation, MobLocation);
        NearestCharacter = Cast<AMainPaperCharacter>(copy_array_of_main_characters[0]);
    }
    for(auto &i : copy_array_of_main_characters){
        FVector CurrentActorLocation = i->GetActorLocation();
        float Distance = FVector::DistSquared(CurrentActorLocation, MobLocation);
        if(Distance > NearestDistance){
            NearestDistance = Distance;
            NearestActorLocation = CurrentActorLocation;
            NearestCharacter = Cast<AMainPaperCharacter>(i);
        }
    }
    return NearestCharacter;
}

void APredatorAIController::MoveToTarget()
{
    if(TargetMainCharacter == nullptr){
        TargetMainCharacter = FindTarget();
    }
    if(TargetMainCharacter != nullptr){
        NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
        MoveToActor(TargetMainCharacter, 2.0f);
        
    } else {
        UE_LOG(LogTemp, Warning, TEXT("No_target_found"));
    }
}

void APredatorAIController::TriggerAttack()
{
    if(bCanAttack)
    {
        if(TargetMainCharacter == nullptr)
        {
            TargetMainCharacter = FindTarget();
        }
        if(TargetMainCharacter != nullptr)
        {
            World->PredatorIsAttacking(TargetMainCharacter, m_Predator);
            bCanAttack = false;
            GetWorldTimerManager().SetTimer(TimerHandle, this, &APredatorAIController::ResetAttack, AttackInterval, false);
        }

    }
}

void APredatorAIController::ResetAttack()
{
    bCanAttack = true;
}