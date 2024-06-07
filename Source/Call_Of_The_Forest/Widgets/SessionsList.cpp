// Fill out your copyright notice in the Description page of Project Settings.

#include "SessionsList.h"


void USessionsList::Join() {
    APlayerController* PlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
	  ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
    ASessionConnect::GetCurrentSession()->JoinSession(FName(*LobbyText), LocalPlayer, PlayerController);		
}
void USessionsList::SetLobbyName() {
  LobbyText = ASessionConnect::GetCurrentSession()->GetText();
  if (LobbyText != FString("NO LOBBY")) {
    Lobby->SetText(FText::AsCultureInvariant(LobbyText));
    b_is_visible = true;
  }
}

void USessionsList::NativeOnInitialized() {
  APlayerController* PlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
  ASessionConnect::GetCurrentSession()->FindSessions(LocalPlayer);
  JoinLobbyOne->OnClicked.AddDynamic(this, &USessionsList::Join);
  Find->OnClicked.AddDynamic(this, &USessionsList::SetLobbyName);
  Super::NativeOnInitialized();
}
