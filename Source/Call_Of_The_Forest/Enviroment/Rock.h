// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnviromentObject.h"
#include "Rock.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API ARock : public AEnviromentObject
{
	GENERATED_BODY()

	ARock();
private:
	UPROPERTY()
	UPaperFlipbookComponent* RockComponent;
	
};
