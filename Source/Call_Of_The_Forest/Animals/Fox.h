// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animal.h"
#include "Fox.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API AFox : public AAnimal
{
	GENERATED_BODY()
public:
	AFox();
	virtual void UpdateAnimalSprite() override;
	virtual void Die() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void SetAnimalSprite(EAnimalState AnimalState);

protected:
	UPROPERTY()
	TMap<EAnimalState, UPaperFlipbook*> DirectionToFoxSprite;
	
};
