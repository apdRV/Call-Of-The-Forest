

#include "PlayOnline.h"


void UPlayOnline::TryStartGame() {
  APlayerController* PlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
  ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
  ASessionConnect::GetCurrentSession()->CreateSession(FName(*AMyDatabase::GetName()), LocalPlayer, PlayerController);
}


void UPlayOnline::NativeOnInitialized() {
  CreateGame->OnClicked.AddDynamic(this, &UPlayOnline::TryStartGame);
  Super::NativeOnInitialized();
}
