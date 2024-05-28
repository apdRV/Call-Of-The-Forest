// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Enviroment/EnviromentObject.h"
#include "EnviromentSpawner.generated.h"

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
