// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ResourceBaseClass/ResourceBase.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include <random>
#include "Stone.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API AStone : public AResourceBase
{
	GENERATED_BODY()
	
public:
	AStone();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stone")
    UPaperFlipbookComponent* StoneComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Value;

};
