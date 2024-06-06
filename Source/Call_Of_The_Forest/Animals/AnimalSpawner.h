// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Animal.h"
#include <random>
#include "Rabbit.h"
#include "Animal.h"
#include "Boar.h"
#include "Deer.h"
#include "Predator.h"
#include "Wolf.h"
#include "Fox.h"
#include "Bear.h"
#include "Math/UnrealMathUtility.h"
#include "AnimalsAIController.h"
#include "PredatorAIController.h"
#include "AnimalSpawner.generated.h"

enum class EAnimalType{
	Rabbit,
	Boar,
	Deer,
	Wolf,
	Fox,
	Bear
};

UCLASS()
class CALL_OF_THE_FOREST_API AAnimalSpawner : public AActor
{
	GENERATED_BODY()
	
public:	

	AAnimalSpawner();

protected:

	virtual void BeginPlay() override;

	void SpawnAnimals();
	
	EAnimalType GenerateRandomAnimal();

};
