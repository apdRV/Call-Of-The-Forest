// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "../Character/MainPaperCharacter.h"
#include "../World/StaticWorld.h"
#include "Mob.h"
#include "NavigationSystem.h"
#include "MobAIController.generated.h"

/**
 *
 */
UCLASS()
class CALL_OF_THE_FOREST_API AMobAIController : public AAIController {

  GENERATED_BODY()
public:
  AMobAIController();

	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

protected:
  void BeginPlay() override;

  void Tick(float Delta) override;

  virtual void OnPossess(APawn *InPawn) override;

private:
  UPROPERTY()
  FTimerHandle TimerHandle;

  UPROPERTY()
  bool bCanAttack;

  UPROPERTY()
  float AttackInterval;

  UPROPERTY()
  class AStaticWorld *World;

  UPROPERTY()
  class AMainPaperCharacter *TargetMainCharacter;

  UPROPERTY()
  class AMob *m_Mob;

  UPROPERTY()
  class UNavigationSystemV1* NavArea;

  UFUNCTION(BlueprintCallable, Category = "Moving")
  AMainPaperCharacter* FindTarget();

  UFUNCTION(BlueprintCallable, Category = "Moving")
  void TriggerAttack();

  UFUNCTION(BlueprintCallable, Category = "Moving")
  void MoveToTarget();

  UFUNCTION()
  void ResetAttack();

};
