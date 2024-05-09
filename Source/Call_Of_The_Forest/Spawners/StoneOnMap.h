// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "../World/StaticWorld.h"
#include "StoneOnMap.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API AStoneOnMap : public APaperFlipbookActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, Category=paper)
	UPaperFlipbookComponent* StoneMapComponent;

	UPROPERTY()
	AStaticWorld* World; 
public:
	AStoneOnMap();

	virtual void BeginPlay() override {
    	Super::BeginPlay();
		World->AddActor("Stone", this);
	}

	void Attacked(){
	}
	
};
