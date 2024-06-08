// Fill out your copyright notice in the Description page of Project Settings.


#include "MobAIController.h"
#include "../Multiplayer/SessionConnect.h"
#include "NavigationSystem.h"

AMobAIController::AMobAIController()
{
    PrimaryActorTick.bCanEverTick = true;
    m_Mob = nullptr;
    bCanAttack = true;
    AttackInterval = 1.0f;
    TargetMainCharacter = nullptr;
    if(World == nullptr){
        UE_LOG(LogTemp, Warning, TEXT("World is null"));
    }
}
void AMobAIController::BeginPlay()
{
    Super::BeginPlay();
    World = AStaticWorld::GetStaticWorld();
    NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

}

void AMobAIController::Tick(float Delta)
{
    if (!World) {
        World = AStaticWorld::GetStaticWorld();
    }
    Super::Tick(Delta);
    if(m_Mob != nullptr && m_Mob->GetbIsTriggered()){
        MoveToTarget();
        TriggerAttack();
    }
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
    std::vector<AMainPaperCharacter*> copy_array_of_main_characters = World->GetCharacters();
    
    if(copy_array_of_main_characters.size() == 0){
        UE_LOG(LogTemp, Warning, TEXT("No_main_characters_in_area"));
        return NearestCharacter;
    }
    if (copy_array_of_main_characters[0] !=nullptr) {
        NearestActorLocation = copy_array_of_main_characters[0]->GetActorLocation();
        NearestDistance = FVector::DistSquared(NearestActorLocation, MobLocation);
        NearestCharacter = copy_array_of_main_characters[0];
    }
    if (!NearestCharacter && copy_array_of_main_characters.size() > 1 && copy_array_of_main_characters[1]) {
        NearestActorLocation = copy_array_of_main_characters[1]->GetActorLocation();
        NearestDistance = FVector::DistSquared(NearestActorLocation, MobLocation);
        NearestCharacter = copy_array_of_main_characters[1];
    }

    if (copy_array_of_main_characters.size() > 3) {
        if (copy_array_of_main_characters[2]!=nullptr) {
            FVector CurrentActorLocation = copy_array_of_main_characters[2]->GetActorLocation();
            float Distance = FVector::DistSquared(CurrentActorLocation, MobLocation);
            if(Distance < NearestDistance){
                NearestDistance = Distance;
                NearestActorLocation = CurrentActorLocation;
                NearestCharacter = copy_array_of_main_characters[2];
            }
        }
    }

    return NearestCharacter;
}

void AMobAIController::TriggerAttack()
{
    if(bCanAttack){
        if(TargetMainCharacter == nullptr)
        {
            TargetMainCharacter = FindTarget();
        }
        if(TargetMainCharacter != nullptr)
        {
            if(TargetMainCharacter->GetActorLocation().Y - m_Mob->GetActorLocation().Y < 0.0f)
            {
                m_Mob->SetMobState(EMobState::IdleLeftDown);
                m_Mob->SetLastMobState(EMobState::IdleLeftDown);
            }
            else{
                m_Mob->SetMobState(EMobState::IdleRightUp);
                m_Mob->SetLastMobState(EMobState::IdleRightUp);
            }
            World->MobIsAttacking(TargetMainCharacter, m_Mob);
            bCanAttack = false;
            GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMobAIController::ResetAttack, AttackInterval, false);
        }
    }
}

void AMobAIController::MoveToTarget()
{
    if(TargetMainCharacter == nullptr){
        TargetMainCharacter = FindTarget();
    }
    if(TargetMainCharacter != nullptr && !m_Mob->GetbIsDead()){
        NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
        MoveToActor(TargetMainCharacter, 2.0f);
    } else {
        UE_LOG(LogTemp, Warning, TEXT("No_target_found"));
    }
}

void AMobAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
}

void AMobAIController::ResetAttack()
{
    bCanAttack = true;
}
