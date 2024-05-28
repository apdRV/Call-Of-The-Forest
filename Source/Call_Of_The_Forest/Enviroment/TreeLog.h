// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnviromentObject.h"
#include "TreeLog.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API ATreeLog : public AEnviromentObject
{
	GENERATED_BODY()

	ATreeLog();

private:
	UPROPERTY()
	UPaperFlipbookComponent* TreeLogComponent;
	
};
