// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Predator.h"
#include "Wolf.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API AWolf : public APredator
{
	GENERATED_BODY()
public:
	AWolf();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

private:

	virtual void UpdatePredatorSprite() override;

	virtual void Die() override;

	void SetPredatorSprite(EPredatorState PredatorState);

	UPROPERTY()
	TMap<EPredatorState, UPaperFlipbook*> DirectionToWolfSprite;
};
