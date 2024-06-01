// Fill out your copyright notice in the Description page of Project Settings.

#include "JoinSession.h"


void UJoinSession::TryStartGame() {

}


void UJoinSession::NativeOnInitialized() {

  APlayerController* PlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
  ASessionConnect::GetCurrentSession()->CreateSession(FName(*AMyDatabase::GetName()), LocalPlayer, PlayerController);


  FText Name = FText::AsCultureInvariant(AMyDatabase::GetName());
  UserNameOne->SetText(Name);

  StartGame->OnClicked.AddDynamic(this, &UJoinSession::TryStartGame);
  Super::NativeOnInitialized();
}
