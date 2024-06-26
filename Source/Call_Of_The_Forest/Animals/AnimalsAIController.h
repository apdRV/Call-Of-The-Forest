// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Animal.h"
#include "TimerManager.h"
#include "Rabbit.h"
#include "Math/Vector.h"
#include "NavigationSystem.h"
#include "../Character/MainPaperCharacter.h"
#include "AnimalsAIController.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API AAnimalsAIController : public AAIController
{
	GENERATED_BODY()
public:
  	AAnimalsAIController();

protected:
	void BeginPlay() override;

	void Tick(float Delta) override;

	virtual void OnPossess(APawn *InPawn) override;

private:
	UPROPERTY()
	class AStaticWorld *World;

	UPROPERTY()
	class AAnimal *bAnimal;

	UPROPERTY()
	bool bCanMove;

	UPROPERTY()
	float bWaitTime;

	UPROPERTY()
    FTimerHandle TimerHandle;

	UPROPERTY()
	float bSearchRadius;

	UPROPERTY()
	class UNavigationSystemV1* NavArea;

	UFUNCTION()
	void RandomMove();

	UFUNCTION()
	void ResetbCanMove();

	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

};
