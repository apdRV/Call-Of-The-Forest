// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobsSpawner.h"
#include <random>
#include "Mob.h"
#include "SkeletonSpawner.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API ASkeletonSpawner : public AMobsSpawner
{
	GENERATED_BODY()

public:
	ASkeletonSpawner() : AMobsSpawner(0)
	{
	}
	void SpawnSkeletons();
protected:
	virtual void BeginPlay() override;
	
};
