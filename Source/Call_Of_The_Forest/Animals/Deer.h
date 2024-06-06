// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animal.h"
#include "Deer.generated.h"

/**
 *
 */
UCLASS()
class CALL_OF_THE_FOREST_API ADeer : public AAnimal {
  GENERATED_BODY()
public:
  ADeer();

  virtual void Tick(float DeltaTime) override;

  virtual void BeginPlay() override;

private:
  virtual void UpdateAnimalSprite() override;

  void SetAnimalSprite(EAnimalState AnimalState);

  virtual void Die() override;

  UPROPERTY()
  TMap<EAnimalState, UPaperFlipbook *> DirectionToDeerSprite;
};
