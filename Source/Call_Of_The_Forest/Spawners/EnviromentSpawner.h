// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnviromentSpawner.generated.h"

enum class EEnviromentObjectType
{
	Rock,
	Bush,
	AppleTree,
	SimpleTree
};

UCLASS()
class CALL_OF_THE_FOREST_API AEnviromentSpawner : public AActor
{
	GENERATED_BODY()
	
public:	

	AEnviromentSpawner();

protected:

	virtual void BeginPlay() override;

	void SpawnEnviromentObject();

	EEnviromentObjectType GenerateRandomObject();

};
