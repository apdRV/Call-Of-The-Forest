// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Database/MyDatabase.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Internationalization/Text.h"
#include "../Multiplayer/SessionConnect.h"
#include <memory>
#include "PlayOnline.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API UPlayOnline : public UUserWidget
{
public:
  GENERATED_BODY()
  virtual void NativeOnInitialized() final;

  UFUNCTION()
  virtual void TryStartGame();

  UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls",
            meta = (BindWidget))
  UButton *CreateGame = nullptr;
};
