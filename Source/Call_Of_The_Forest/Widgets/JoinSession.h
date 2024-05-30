// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Database/MyDatabase.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "CoreMinimal.h"
#include "Internationalization/Text.h"
#include <memory>
#include "JoinSession.generated.h"

/**
 *
 */
UCLASS()
class CALL_OF_THE_FOREST_API UJoinSession : public UUserWidget {
public:
  GENERATED_BODY()
  virtual void NativeOnInitialized() final;

  UFUNCTION()
  virtual void TryStartGame();

  UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls",
            meta = (BindWidget))
  UTextBlock *UserNameOne = nullptr;

  UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls",
            meta = (BindWidget))
  UTextBlock *UserNameTwo = nullptr;

  UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls",
            meta = (BindWidget))
  UButton *StartGame = nullptr;

  UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls",
            meta = (BindWidget))
  bool ready_to_play = false;
};
