// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ResourceBaseClass/ResourceBase.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Meat.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API AMeat : public AResourceBase
{
	GENERATED_BODY()

public:
	AMeat();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Meat")
    UPaperFlipbookComponent* MeatComponent;

protected:
	virtual void BeginPlay() override;

};
