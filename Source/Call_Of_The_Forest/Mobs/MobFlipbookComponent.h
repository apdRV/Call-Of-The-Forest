// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbook.h"
#include "PaperSprite.h"
#include "PaperFlipbookComponent.h"
#include "MobFlipbookComponent.generated.h"

/**
 * 
 */
UENUM(BlueprintType, Category = "Animation")
enum class EMobState : uint8{
	LeftDown,
	RightUp,
	IdleLeftDown,
	IdleRightUp,
	AttackLeftDown,
	AttackRightUp,
	DieLeftDown,
	DieRightUp
};

UCLASS()
class CALL_OF_THE_FOREST_API UMobFlipbookComponent : public UPaperFlipbookComponent
{
	GENERATED_BODY()
public:
	UMobFlipbookComponent();
	void UpdateSprite(EMobState State);
	void SetupOwner(UPaperFlipbookComponent* Owner);

protected:
	TMap<EMobState, UPaperFlipbook*> DirectionToSprite;
	class UPaperFlipbookComponent* MobSprite;
	
};
