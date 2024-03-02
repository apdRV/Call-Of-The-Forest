// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeSpawner.h"

// Called when the game starts or when spawned
void ATreeSpawner::BeginPlay()
{
	Super::BeginPlay();
    SpawnTree();
}

void ATreeSpawner::SpawnTree(){
    FRotator Rotation(0, 0, 90);
    for (int l=-7;l<7;l++){
        for (int r=-7;r<7;r++){
            for (int i=0;i<ObjectCount;i++){
                FVector Location = {0, 0, 0.5};
                Location[0] = l * 500 + std::rand() % 500;
                Location[1] = r * 500 + std::rand() % 500;
                GetWorld()->SpawnActor<ATree1>(Location, Rotation);
            }
        }
    }
    
}

