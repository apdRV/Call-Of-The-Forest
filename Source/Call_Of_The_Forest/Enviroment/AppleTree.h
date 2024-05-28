// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnviromentObject.h"
#include "AppleTree.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API AAppleTree : public AEnviromentObject
{
	GENERATED_BODY()

	AAppleTree();

private:
	UPROPERTY()
	UPaperFlipbookComponent* AppleTreeComponent;
	
};
