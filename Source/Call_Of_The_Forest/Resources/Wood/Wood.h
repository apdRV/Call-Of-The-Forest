// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ResourceBaseClass/ResourceBase.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Wood.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API AWood : public AResourceBase
{
	GENERATED_BODY()

public:
	AWood();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Wood")
    UPaperSpriteComponent* Sprite;

protected:
	virtual void BeginPlay() override;
	
};
