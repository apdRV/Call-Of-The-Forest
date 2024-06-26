// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ResourceBaseClass/ResourceBase.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include <random>
#include "TrophyBase.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API ATrophyBase : public AResourceBase
{
	GENERATED_BODY()

public:
	ATrophyBase();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TrophyBase")
    UPaperFlipbookComponent* TrophyBaseComponent;

protected:
};
