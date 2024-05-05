// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainPaperCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "HealtBar.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API UHealtBar : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintPure)
	float CalculateHealthPercentage();

	UPROPERTY(VisibleAnywhere)
	AMainPaperCharacter* Player;
};
