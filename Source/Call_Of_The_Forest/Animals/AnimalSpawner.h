// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Animal.h"
#include <random>
#include "Rabbit.h"
#include "Animal.h"
#include "AnimalsAIController.h"
#include "AnimalSpawner.generated.h"

UCLASS()
class CALL_OF_THE_FOREST_API AAnimalSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnimalSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SpawnAnimals();


};
