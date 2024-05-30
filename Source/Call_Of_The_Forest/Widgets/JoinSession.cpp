// Fill out your copyright notice in the Description page of Project Settings.

#include "JoinSession.h"

void UJoinSession::TryStartGame() {
    
}

void UJoinSession::NativeOnInitialized() {
  StartGame->OnClicked.AddDynamic(this, &UJoinSession::TryStartGame);
  FText Name = FText::AsCultureInvariant(AMyDatabase::GetName());
  UserNameOne->SetText(Name);
  Super::NativeOnInitialized();
}
