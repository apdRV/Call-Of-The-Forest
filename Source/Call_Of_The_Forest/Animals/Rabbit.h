// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animal.h"
#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbook.h"
#include "PaperSprite.h"
#include "PaperFlipbookComponent.h"
#include "Rabbit.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API ARabbit : public AAnimal
{
	GENERATED_BODY()
public:
	ARabbit();
	virtual void UpdateAnimalSprite() override;
	virtual void Die() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void SetAnimalSprite(EAnimalState AnimalState);

protected:
	UPROPERTY()
	TMap<EAnimalState, UPaperFlipbook*> DirectionToRabbitSprite;

};
