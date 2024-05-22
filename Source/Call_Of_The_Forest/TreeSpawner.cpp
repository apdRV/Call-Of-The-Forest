// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeSpawner.h"

// Called when the game starts or when spawned
void ATreeSpawner::BeginPlay()
{
	Super::BeginPlay();
    SpawnTree();
}

void ATreeSpawner::SpawnTree(){
    FRotator Rotation(0, -90, 90);
    for (int l=-7;l<7;l++){
        for (int r=-7;r<7;r++){
            for (int i=0;i<ObjectCount;i++){
                int x = l * 500 + std::rand() % 500;
                int y = r * 500 + std::rand() % 500;
                while (occupiedLocations.find({x, y}) != occupiedLocations.end()) {
                    x = l * 500 + std::rand() % 500;
                    y = r * 500 + std::rand() % 500;
                }
                FVector Location = {x, y, 12};
                for (int dx = -50; dx <= 50; ++dx) {
                    for (int dy = -50; dy <= 50; ++dy) {
                        occupiedLocations.insert({x + dx, y + dy});
                    }
                }
                GetWorld()->SpawnActor<ATree1>(Location, Rotation);
            }
        }
    }
    
}


