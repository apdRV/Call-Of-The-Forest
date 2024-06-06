// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animal.h"
#include "Rabbit.generated.h"

/**
 *
 */
UCLASS()
class CALL_OF_THE_FOREST_API ARabbit : public AAnimal {
  GENERATED_BODY()
public:
  ARabbit();

  virtual void BeginPlay() override;

  virtual void Tick(float DeltaTime) override;

private:
  virtual void UpdateAnimalSprite() override;

  void SetAnimalSprite(EAnimalState AnimalState);

  virtual void Die() override;

  UPROPERTY()
  TMap<EAnimalState, UPaperFlipbook *> DirectionToRabbitSprite;
};
