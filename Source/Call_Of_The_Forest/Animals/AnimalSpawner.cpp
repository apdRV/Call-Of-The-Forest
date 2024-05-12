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
    for (int l = -2; l < 2; l++) {
        for (int r = -2; r < 2; r++) {
            for (int i = 0; i < 2; i++) {
                FVector Location = { 0, 0, 12 };
                Location[0] = l * 500 + FMath::RandRange(0, 500);
                Location[1] = r * 500 + FMath::RandRange(0, 500);
				AController* AIController = GetWorld()->SpawnActor<AAnimalsAIController>(AAnimalsAIController::StaticClass());
				ARabbit* SpawnedMob = GetWorld()->SpawnActor<ARabbit>(Location, Rotation);
				if(SpawnedMob && AIController){
					AIController->Possess(SpawnedMob);   
                    UE_LOG(LogTemp, Warning, TEXT("Rabbit AIPossesed"));
				}
            }
        }
    }
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
}

