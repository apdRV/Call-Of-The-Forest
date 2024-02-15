// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "MainPaperCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API AMainPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test Health") int health = 100;

protected:
	
};
