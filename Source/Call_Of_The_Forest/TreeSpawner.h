// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spawner.h"
#include <random>
#include "Tree1.h"
#include "TreeSpawner.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API ATreeSpawner : public ASpawner
{
	GENERATED_BODY()
	
public:
	ATreeSpawner(): ASpawner(1) {}
	void SpawnTree();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
