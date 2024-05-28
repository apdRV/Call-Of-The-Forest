// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spawner.h"
#include <random>
#include "../Enviroment/Rock.h"
#include "StoneSpawner.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API AStoneSpawner : public ASpawner
{
	GENERATED_BODY()
public:
	AStoneSpawner(): ASpawner(0) {}
	void SpawnStone();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
