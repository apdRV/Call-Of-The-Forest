// Fill out your copyright notice in the Description page of Project Settings.


#include "SproutSpawner.h"
#include "MobAIController.h"
#include "Sprout.h"
#include "Math/UnrealMathUtility.h"

void ASproutSpawner::SpawnSprouts()
{
    FRotator Rotation(0, 0, 0);
    for (int l = -2; l < 2; l++) {
        for (int r = -2; r < 2; r++) {
            for (int i = 0; i < ObjectCount; i++) {
                FVector Location = { 0, 0, 12 };
                Location[0] = l * 500 + FMath::RandRange(0, 500);
                Location[1] = r * 500 + FMath::RandRange(0, 500);
                if (FMath::Abs(Location[0]) > 100.0f && FMath::Abs(Location[1]) > 100.0f) {
                    AController* AIController = GetWorld()->SpawnActor<AMobAIController>(AMobAIController::StaticClass());
                    AMob* SpawnedMob = GetWorld()->SpawnActor<ASprout>(Location, Rotation);
                    if(SpawnedMob && AIController){
                            AIController->Possess(SpawnedMob);    
                        }
                }
            }
        }
    }
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
}

void ASproutSpawner::BeginPlay()
{
    Super::BeginPlay();
    SpawnSprouts();
}
