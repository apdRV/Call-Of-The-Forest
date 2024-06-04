// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DirectionalLight.h"
#include "Misc/OutputDeviceNull.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "DayNightCycle.generated.h"

UCLASS()
class CALL_OF_THE_FOREST_API ADayNightCycle : public AActor
{
	GENERATED_BODY()
	
public:	

	ADayNightCycle();

protected:

	virtual void BeginPlay() override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Replicated, Category = "Sky")
	AActor* sun;

	UPROPERTY(EditAnywhere, Replicated, Category = "Sky")
	ADirectionalLight* lightSource;

	UPROPERTY(EditAnywhere, Replicated, Category = "Sky")
	float turnRate = 3;

	UPROPERTY(ReplicatedUsing = OnRep_TimeOfDay)
	float TimeOfDay;

	UFUNCTION()
	void OnRep_TimeOfDay();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetTimeOfDay(float NewTimeOfDay);

	void UpdateTimeOfDay(float DeltaTime);

	void UpdateLighting();
};
