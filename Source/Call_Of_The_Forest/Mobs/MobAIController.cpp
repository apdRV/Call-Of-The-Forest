// Fill out your copyright notice in the Description page of Project Settings.


#include "MobAIController.h"
#include "Mob.h"
#include "MobFlipbookComponent.h"
#include "NavigationSystem.h"

AMobAIController::AMobAIController()
{
    PrimaryActorTick.bCanEverTick = true;
    World = AStaticWorld::GetStaticWorld();
    m_Mob = nullptr;
    TargetMainCharacter = nullptr;
    if(World == nullptr){
        UE_LOG(LogTemp, Warning, TEXT("World is null"));
    }
}
void AMobAIController::BeginPlay()
{
    Super::BeginPlay();

    NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

    bIsMoving = false;
	
}

void AMobAIController::Tick(float Delta)
{
    Super::Tick(Delta);
    if(m_Mob->GetTriggered()){
        MoveToTarget();
    }

	// if (!bIsMoving && NavArea && m_Mob)
	// {
	// 	SearchForPlayer();
	// }
    // MoveToTarget();
}

void AMobAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    m_Mob = dynamic_cast<AMob*>(InPawn);
    if(m_Mob == nullptr){
        UE_LOG(LogTemp, Warning, TEXT("Mob is null"));
    }
}


AMainPaperCharacter* AMobAIController::FindTarget(){
    AMainPaperCharacter* NearestPlayer;
    FVector MobLocation = m_Mob->GetActorLocation();
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

void AMobAIController::TriggerAttack(FVector TargetLocation,FVector CurrentLocation)
{

    //m_Mob->Attack();
}

void AMobAIController::MoveToTarget()
{
    if(TargetMainCharacter == nullptr){
        TargetMainCharacter = FindTarget();
    }
    if(TargetMainCharacter != nullptr){
        FVector TargetLocation = TargetMainCharacter->GetActorLocation();
        FVector CurrentLocation = m_Mob->GetActorLocation();
        FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
        m_Mob->MoveForwardBackward(Direction.X);
        m_Mob->MoveRightLeft(Direction.Y);
    } else {
        UE_LOG(LogTemp, Warning, TEXT("No_target_found"));
    }
}


void AMobAIController::GenerateRandomSearchLocation()
{
    FNavLocation Location{};
	if (IsValid(NavArea) && m_Mob)
	{
        NavArea->GetRandomReachablePointInRadius(m_Mob->GetActorLocation(), 50.0f, Location);
		RandomLocation = Location.Location;
	} 
}


void AMobAIController::SearchForPlayer()
{
	if (IsValid(NavArea) && m_Mob && !bIsMoving)
	{
		GenerateRandomSearchLocation();
		bIsMoving = true;
        MoveToLocation(RandomLocation);
	}
}


void AMobAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
    bIsMoving = false;
}
