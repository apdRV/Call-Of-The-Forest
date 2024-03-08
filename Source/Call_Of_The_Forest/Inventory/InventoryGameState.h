// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/GameStateBase.h"
#include "InventoryGameState.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API AInventoryGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AInventoryGameState();

	UDataTable* GetItemDB() const;

protected:
	UPROPERTY(EditDefaultsOnly)
	class UDataTable* ItemDB;
};
