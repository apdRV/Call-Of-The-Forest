// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ResourceBaseClass/ResourceBase.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
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

	void Interact_Implementation(APlayerController* Controller) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;
	
};
