// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbook.h"
#include "PaperSprite.h"
#include "PaperFlipbookComponent.h"
#include "RabbitFlipbookComponent.generated.h"

/**
 * 
 */
UENUM(BlueprintType, Category = "Animation")
enum class ERabbitState : uint8{
	LeftDown,
	RightUp,
	IdleLeftDown,
	IdleRightUp,
	DieLeftDown,
	DieRightUp
};

UCLASS()
class CALL_OF_THE_FOREST_API URabbitFlipbookComponent : public UPaperFlipbookComponent
{
	GENERATED_BODY()

public:
	URabbitFlipbookComponent();
	void UpdateSprite(ERabbitState State);
	void SetupOwner(UPaperFlipbookComponent* Owner);

protected:
	TMap<ERabbitState, UPaperFlipbook*> DirectionToSprite;
	class UPaperFlipbookComponent* RabbitSprite;



	
};
