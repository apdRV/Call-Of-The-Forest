// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbook.h"
#include "PaperSprite.h"
#include "PaperFlipbookComponent.h"
#include "MainCharacterSpriteComponent.generated.h"

/**
 * 
 */
UENUM(BlueprintType, Category = "Animation")
enum class EMainCharacterState : uint8{
	Up,
	Down,
	Left,
	Right,
	IdleUp,
	IdleDown,
	IdleLeft,
	IdleRight
};

UCLASS()
class CALL_OF_THE_FOREST_API UMainCharacterSpriteComponent : public UPaperSpriteComponent
{
    GENERATED_BODY()

public:
    UMainCharacterSpriteComponent();
    void UpdateSprite(EMainCharacterState State);
	void SetupOwner(UPaperFlipbookComponent* Owner);

protected:
    TMap<EMainCharacterState, UPaperFlipbook*> DirectionToSprite;
    class UPaperFlipbookComponent* MainCharacterSprite;
};
