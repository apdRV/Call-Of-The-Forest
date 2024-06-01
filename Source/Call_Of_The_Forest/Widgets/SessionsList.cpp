// Fill out your copyright notice in the Description page of Project Settings.

#include "SessionsList.h"


void USessionsList::Join() {
    APlayerController* PlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
	  ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
    ASessionConnect::GetCurrentSession()->JoinSession(FName(*LobbyText), LocalPlayer, PlayerController);
    		
}
void USessionsList::NativeOnInitialized() {

  APlayerController* PlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
  
    TSharedPtr<FOnlineSessionSearch> SessionSearch = ASessionConnect::GetCurrentSession()->FindSessions(LocalPlayer);
    for (int SearchIdx = 0; SearchIdx < SessionSearch->SearchResults.Num(); SearchIdx++) {
        if (SearchIdx == 0) LobbyText = SessionSearch->SearchResults[SearchIdx].GetSessionIdStr();
    }
    Lobby->SetText(FText::AsCultureInvariant(LobbyText));

  JoinLobbyOne->OnClicked.AddDynamic(this, &USessionsList::Join);
  Super::NativeOnInitialized();
}
