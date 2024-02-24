// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <random>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wood.generated.h"

UCLASS()
class CALL_OF_THE_FOREST_API AWood : public AActor
{
	GENERATED_BODY()
	int Quantity = 0;
	
public:	
	// Sets default values for this actor's properties
	AWood();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
