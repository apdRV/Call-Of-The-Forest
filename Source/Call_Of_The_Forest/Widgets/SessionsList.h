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
#include "OnlineSessionSettings.h"
#include <memory>
#include "SessionsList.generated.h"

/**
 *
 */

UCLASS()
class CALL_OF_THE_FOREST_API USessionsList : public UUserWidget {
public:
  GENERATED_BODY()
  virtual void NativeOnInitialized() final;

  UFUNCTION()
  void Join();

  UFUNCTION()
  void SetLobbyName();

  FString LobbyText;

  UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls",
            meta = (BindWidget))
  UTextBlock *Lobby = nullptr;

  UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls",
            meta = (BindWidget))
  UButton *JoinLobbyOne = nullptr;

  UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls",
            meta = (BindWidget))
  UButton *Find = nullptr;

  UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls",
            meta = (BindWidget))
  bool b_is_visible = false;

};
