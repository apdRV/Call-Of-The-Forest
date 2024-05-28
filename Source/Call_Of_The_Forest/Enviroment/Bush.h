// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnviromentObject.h"
#include "Bush.generated.h"

UCLASS()
class CALL_OF_THE_FOREST_API ABush : public AEnviromentObject
{
	GENERATED_BODY()

	ABush();

private:
	UPROPERTY()
	UPaperFlipbookComponent* BushComponent;	
};
