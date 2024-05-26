// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainPaperCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MiniInventory.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API UMiniInventory : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintPure)
	int CalculateWoodQuantity();

	UFUNCTION(BlueprintPure)
	int CalculateStoneQuantity();

	UFUNCTION(BlueprintPure)
	int CalculateTrophyQuantity();

	UFUNCTION(BlueprintPure)
	int CalculateMeatQuantity();

	UPROPERTY(VisibleAnywhere)
	AMainPaperCharacter* Player;
	
};
