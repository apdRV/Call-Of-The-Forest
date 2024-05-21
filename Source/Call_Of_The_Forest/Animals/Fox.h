// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Predator.h"
#include "Fox.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API AFox : public APredator
{
	GENERATED_BODY()
public:
	AFox();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

	virtual void UpdatePredatorSprite() override;

	virtual void Die() override;

	void SetPredatorSprite(EPredatorState PredatorState);
	
	UPROPERTY()
	TMap<EPredatorState, UPaperFlipbook*> DirectionToFoxSprite;
	
};
