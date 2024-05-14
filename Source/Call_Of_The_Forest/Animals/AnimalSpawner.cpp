// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalSpawner.h"

// Sets default values
AAnimalSpawner::AAnimalSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAnimalSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnAnimals();
	
}

void AAnimalSpawner::SpawnAnimals()
{
    FRotator Rotation(0, 0, 0);
    for (int l = -4; l < 4; l++) {
        for (int r = -4; r < 4; r++) {
            for (int i = 0; i < 2; i++) {
                FVector Location = { 0, 0, 12 };
                Location[0] = l * 500 + FMath::RandRange(0, 500);
                Location[1] = r * 500 + FMath::RandRange(0, 500);
                int Animal_type = FMath::RandRange(1, 6);
                AAnimalsAIController* AIController = nullptr;
                APredatorAIController* AIPredatorController = nullptr;
                if(Animal_type == 1){
                    AIController = GetWorld()->SpawnActor<AAnimalsAIController>(AAnimalsAIController::StaticClass());
                    ARabbit* SpawnedRabbit = GetWorld()->SpawnActor<ARabbit>(Location, Rotation);
                    if(SpawnedRabbit && AIController){
                        AIController->Possess(SpawnedRabbit);   
                        UE_LOG(LogTemp, Warning, TEXT("Rabbit AIPossesed"));
                    }
                }
                else if(Animal_type == 2){
                    AIController = GetWorld()->SpawnActor<AAnimalsAIController>(AAnimalsAIController::StaticClass());
                    ABoar* SpawnedBoar = GetWorld()->SpawnActor<ABoar>(Location, Rotation);
                    if(SpawnedBoar && AIController){
                        AIController->Possess(SpawnedBoar);   
                        UE_LOG(LogTemp, Warning, TEXT("Boar AIPossesed"));
                    }
                }
                else if(Animal_type == 3){
                    AIController = GetWorld()->SpawnActor<AAnimalsAIController>(AAnimalsAIController::StaticClass());
                    ADeer* SpawnedDeer = GetWorld()->SpawnActor<ADeer>(Location, Rotation);
                    if(SpawnedDeer && AIController){
                        AIController->Possess(SpawnedDeer);   
                        UE_LOG(LogTemp, Warning, TEXT("Deer AIPossesed"));
                    }
                }
                else if(Animal_type == 4){
                    AIPredatorController = GetWorld()->SpawnActor<APredatorAIController>(APredatorAIController::StaticClass());
                    AWolf* SpawnedWolf = GetWorld()->SpawnActor<AWolf>(Location, Rotation);
                    if(SpawnedWolf && AIPredatorController){
                        AIPredatorController->Possess(SpawnedWolf);
                        UE_LOG(LogTemp, Warning, TEXT("Wolf AIPossesed"));
                    }
                }
                else if(Animal_type == 5){
                    AIPredatorController = GetWorld()->SpawnActor<APredatorAIController>(APredatorAIController::StaticClass());
                    AFox* SpawnedFox = GetWorld()->SpawnActor<AFox>(Location, Rotation);
                    if(SpawnedFox && AIPredatorController){
                        AIPredatorController->Possess(SpawnedFox);
                        UE_LOG(LogTemp, Warning, TEXT("Fox AIPossesed"));
                    }
                }
                else if(Animal_type == 6){
                    AIPredatorController = GetWorld()->SpawnActor<APredatorAIController>(APredatorAIController::StaticClass());
                    ABear* SpawnedBear = GetWorld()->SpawnActor<ABear>(Location, Rotation);
                    if(SpawnedBear && AIPredatorController){
                        AIPredatorController->Possess(SpawnedBear);
                        UE_LOG(LogTemp, Warning, TEXT("Fox AIPossesed"));
                    }
                }
            }
        }
    }
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
}

