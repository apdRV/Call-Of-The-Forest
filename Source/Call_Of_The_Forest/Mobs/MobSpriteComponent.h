// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbook.h"
#include "PaperSprite.h"
#include "PaperFlipbookComponent.h"
#include "MobSpriteComponent.generated.h"

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
class CALL_OF_THE_FOREST_API UMobSpriteComponent : public UPaperSpriteComponent
{
	GENERATED_BODY()

public:
	UMobSpriteComponent();
	void UpdateSprite(EMobState State);
	void SetupOwner(UPaperFlipbookComponent* Owner);

//protected:
	TMap<EMobState, UPaperFlipbook*> DirectionToSprite;
	class UPaperFlipbookComponent* MobSprite;
	
};
