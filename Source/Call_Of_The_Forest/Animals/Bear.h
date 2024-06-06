// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Predator.h"
#include "Bear.generated.h"

/**
 *
 */
UCLASS()
class CALL_OF_THE_FOREST_API ABear : public APredator {
  GENERATED_BODY()
public:
  ABear();

  virtual void BeginPlay() override;

  virtual void Tick(float DeltaTime) override;

private:
  virtual void UpdatePredatorSprite() override;

  void SetPredatorSprite(EPredatorState PredatorState);

  virtual void Die() override;

  UPROPERTY()
  TMap<EPredatorState, UPaperFlipbook *> DirectionToBearSprite;
};
