// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnviromentObject.h"
#include "SimpleTree.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API ASimpleTree : public AEnviromentObject
{
	GENERATED_BODY()
	
	ASimpleTree();
private:
	UPROPERTY()
	UPaperFlipbookComponent* SimpleTreeComponent;
};
