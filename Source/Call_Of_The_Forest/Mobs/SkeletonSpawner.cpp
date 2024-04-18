// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonSpawner.h"

void ASkeletonSpawner::SpawnSkeletons()
{
    FRotator Rotation(0, 0, 0);
    for (int l=-7;l<7;l++){
        for (int r=-7;r<7;r++){
            for (int i=0;i<ObjectCount;i++){
                FVector Location = {0, 0, 0};
                Location[0] = l * 500 + std::rand() % 500;
                Location[1] = r * 500 + std::rand() % 500;
                GetWorld()->SpawnActor<AMob>(Location, Rotation);
            }
        }
    }
}

void ASkeletonSpawner::BeginPlay()
{
    Super::BeginPlay();
    SpawnSkeletons();
}

