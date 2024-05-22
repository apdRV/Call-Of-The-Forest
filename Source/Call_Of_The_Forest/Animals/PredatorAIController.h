// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Predator.h"
#include "Math/Vector.h"
#include "NavigationSystem.h"
#include "Engine/EngineTypes.h"
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
	FTimerHandle TimerHandle;

	UPROPERTY()
	bool bCanMove;

	UPROPERTY()
	float bWaitTime;

	UPROPERTY()
	bool bCanAttack;

	UPROPERTY()
	float bAttackInterval;

	UPROPERTY()
	class AStaticWorld *World;

	UPROPERTY()
	class APredator *bPredator;

	UPROPERTY()
	class AMainPaperCharacter *bTargetMainCharacter;
	
	UPROPERTY()
	int wait_time;

	UPROPERTY()
	class UNavigationSystemV1* NavArea;

	UPROPERTY()
	FVector RandomLocation = FVector();

	UPROPERTY()
	float SearchRadius;

	UFUNCTION()
	AMainPaperCharacter* FindTarget();

	UFUNCTION()
	void TriggerAttack();

	UFUNCTION()
	void ResetAttack();

	UFUNCTION()
	void ResetbCanMove();
	
	UFUNCTION()
	void MoveToTarget();

	UFUNCTION()
	void RandomMove();

	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	
};
