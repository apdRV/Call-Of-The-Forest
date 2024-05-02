// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonSpawner.h"
#include <cmath>

void ASkeletonSpawner::SpawnSkeletons()
{
    FRotator Rotation(0, 0, 0);
    for (int l=-7;l<7;l++){
        for (int r=-7;r<7;r++){
            for (int i=0;i<ObjectCount;i++){
                FVector Location = {0, 0, 12};
                Location[0] = l * 500 + std::rand() % 500;
                Location[1] = r * 500 + std::rand() % 500;
                if(abs(Location[0]) > 20 && abs(Location[1]) > 20){
                    GetWorld()->SpawnActor<AMob>(Location, Rotation);
                }
            }
        }
    }
}

void ASkeletonSpawner::BeginPlay()
{
    Super::BeginPlay();
    SpawnSkeletons();
}

