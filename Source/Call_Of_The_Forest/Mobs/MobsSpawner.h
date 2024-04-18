// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MobsSpawner.generated.h"

UCLASS()
class CALL_OF_THE_FOREST_API AMobsSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	explicit AMobsSpawner();
	explicit AMobsSpawner(int ObjectCount_);

protected:

public:	
	int ObjectCount;

	TSubclassOf<AActor> SpawnerClass;

};
