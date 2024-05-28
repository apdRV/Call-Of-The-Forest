// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnviromentObject.h"
#include "TreeStump.generated.h"

UCLASS()
class CALL_OF_THE_FOREST_API ATreeStump : public AEnviromentObject
{
	GENERATED_BODY()

	ATreeStump();

private:
	UPROPERTY()
	UPaperFlipbookComponent* TreeStumpComponent;
	
};
