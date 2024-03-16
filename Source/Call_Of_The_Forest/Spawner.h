// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include "Spawner.generated.h"

UCLASS()
class CALL_OF_THE_FOREST_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	explicit ASpawner();
	explicit ASpawner(int ObjectCount_);
	
public:
	int ObjectCount;

	TSubclassOf<AActor> SpawnerClass;

	
};