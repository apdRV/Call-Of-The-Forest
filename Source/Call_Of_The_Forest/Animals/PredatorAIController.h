// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Predator.h"
#include "Math/Vector.h"
#include "NavigationSystem.h"
#include "../Character/MainPaperCharacter.h"
#include "PredatorAIController.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API APredatorAIController : public AAIController
{
	GENERATED_BODY()

public:
  	APredatorAIController();

protected:
	void BeginPlay() override;

	void Tick(float Delta) override;

	virtual void OnPossess(APawn *InPawn) override;

private:
	UPROPERTY()
	class AStaticWorld *World;

	UPROPERTY()
	class APredator *m_Predator;
	
	UPROPERTY()
	int wait_time;

	UPROPERTY()
	class UNavigationSystemV1* NavArea;

	UPROPERTY()
	FVector RandomLocation = FVector();

	UFUNCTION(BlueprintCallable, Category = "Moving")
	void GenerateRandomLocation();

	UFUNCTION(BlueprintCallable, Category = "Moving")
	void RandomMove();

	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
private:
    FTimerHandle TimerHandle;
	
};
