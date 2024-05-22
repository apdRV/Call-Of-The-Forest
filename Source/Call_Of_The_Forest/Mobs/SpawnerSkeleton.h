// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobsSpawner.h"
#include "SpawnerSkeleton.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API ASpawnerSkeleton : public AMobsSpawner
{
	GENERATED_BODY()
public:
  ASpawnerSkeleton() : AMobsSpawner(2) {}
  void SpawnSkeletons();

protected:
  virtual void BeginPlay() override;
};
