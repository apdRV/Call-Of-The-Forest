// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneSpawner.h"
#include <set>
#include <utility>

void AStoneSpawner::BeginPlay()
{
	Super::BeginPlay();
    SpawnStone();
}

void AStoneSpawner::SpawnStone(){
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
                GetWorld()->SpawnActor<ARock>(Location, Rotation);
                for (int dx = -50; dx <= 50; ++dx) {
                    for (int dy = -50; dy <= 50; ++dy) {
                        occupiedLocations.insert({x + dx, y + dy});
                    }
                }
            }
        }
    }
}