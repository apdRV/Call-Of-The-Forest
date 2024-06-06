// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobsSpawner.h"
#include "MushroomSpawner.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API AMushroomSpawner : public AMobsSpawner
{
	GENERATED_BODY()
public:
  AMushroomSpawner() : AMobsSpawner(1) {}
  void SpawnMushrooms();

protected:
  virtual void BeginPlay() override;
};
