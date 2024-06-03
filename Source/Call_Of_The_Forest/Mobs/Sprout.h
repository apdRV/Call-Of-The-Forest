// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mob.h"
#include "Sprout.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API ASprout : public AMob
{
	GENERATED_BODY()
	ASprout();
	virtual void UpdateMobSprite() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetMobSprite(EMobState MobState) override;

protected:
	UPROPERTY()
	TMap<EMobState, UPaperFlipbook*> DirectionToSproutSprite;
	
};
