// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobsSpawner.h"
#include "SproutSpawner.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API ASproutSpawner : public AMobsSpawner
{
	GENERATED_BODY()
public:
	ASproutSpawner() : AMobsSpawner(1) {}
	void SpawnSprouts();

protected:
  virtual void BeginPlay() override;
	
};
