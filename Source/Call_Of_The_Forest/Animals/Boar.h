// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animal.h"
#include "Boar.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API ABoar : public AAnimal
{
	GENERATED_BODY()
public:
	ABoar();
	virtual void UpdateAnimalSprite() override;
	virtual void Die() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void SetAnimalSprite(EAnimalState AnimalState);

protected:
	UPROPERTY()
	TMap<EAnimalState, UPaperFlipbook*> DirectionToBoarSprite;
	
};
