// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <chrono>
#include <cstdlib>
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Generator.generated.h"

UCLASS()
class CALL_OF_THE_FOREST_API AGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	bool is_rain = false;
	bool is_spawned = false;
	bool is_destroyed = true;
	int random_num = 100;
	UNiagaraSystem* Rain;
	UNiagaraComponent* CurrentRain;
	// Sets default values for this actor's properties
	AGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
