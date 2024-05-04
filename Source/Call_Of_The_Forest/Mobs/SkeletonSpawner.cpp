// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonSpawner.h"
#include "MobAIController.h"
#include <cmath>

void ASkeletonSpawner::SpawnSkeletons()
{
    FRotator Rotation(0, 0, 0);
    for (int l = -3; l < 3; l++) {
        for (int r = -3; r < 3; r++) {
            for (int i = 0; i < ObjectCount; i++) {
                FVector Location = { 0, 0, 12 };
                Location[0] = l * 500 + FMath::RandRange(0, 500);
                Location[1] = r * 500 + FMath::RandRange(0, 500);
                if (FMath::Abs(Location[0]) > 20 && FMath::Abs(Location[1]) > 20) {
                    AMob* SpawnedMob = GetWorld()->SpawnActor<AMob>(Location, Rotation);
                   if(SpawnedMob){
                        AController* AIController = GetWorld()->SpawnActor<AMobAIController>(AMobAIController::StaticClass());
                        if(AIController){
                            AIController->Possess(SpawnedMob);
                        }
                   }
                }
            }
        }
    }
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
}


void ASkeletonSpawner::BeginPlay()
{
    Super::BeginPlay();
    SpawnSkeletons();
}

