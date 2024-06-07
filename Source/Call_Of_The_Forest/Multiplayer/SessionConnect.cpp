// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionConnect.h"

ASessionConnect* ASessionConnect::CurrentSession = nullptr;
UWorld* ASessionConnect::WWorld = nullptr;
int ASessionConnect::PlayerID = 0;
// Sets default values
ASessionConnect::ASessionConnect()
{
	if (CurrentSession == nullptr) {
		CurrentSession = this;
	}
    if (SessionSearch == nullptr) SessionSearch = MakeShareable(new FOnlineSessionSearch());
}

ASessionConnect::~ASessionConnect()
{
    
}

void ASessionConnect::BeginPlay(){
	Super::BeginPlay();
}

ASessionConnect* ASessionConnect::GetCurrentSession() {
	return CurrentSession;
}

void ASessionConnect::SetWorld(UWorld* World) {
    WWorld = World;
}

int ASessionConnect::GetID() {
    return PlayerID;
}

void ASessionConnect::FindSessions(ULocalPlayer* LocalPlayer) {
    IOnlineSubsystem* OnlineSub = Online::GetSubsystem(WWorld);
    
    if (OnlineSub)
    {
        IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
        if (Sessions.IsValid() && LocalPlayer)
        {

            if (Sessions->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), SessionSearch.ToSharedRef())) {
                UE_LOG(LogTemp, Warning, TEXT("OK"));
            }    
                    
        }
    }
}

FString ASessionConnect::GetText() {
    if (SessionSearch->SearchResults.Num() > 0) {
            UE_LOG(LogTemp, Warning, TEXT("OK2"));
            return SessionSearch->SearchResults[0].Session.OwningUserName;
    }
    else return FString("NO LOBBY");
}

void ASessionConnect::CreateSession(FName SessionName, ULocalPlayer* LocalPlayer, APlayerController* PlayerController)
{
    PlayerID = 0;
    IOnlineSubsystem* OnlineSub = Online::GetSubsystem(WWorld);
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
	if (Sessions.IsValid() && LocalPlayer)
	{
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = true;
		SessionSettings.bUsesPresence = true;
		SessionSettings.NumPublicConnections = 2;
		SessionSettings.NumPrivateConnections = 2   ;
		SessionSettings.bAllowInvites = true;
		SessionSettings.bAllowJoinInProgress = true;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bAllowJoinViaPresence = true;
		SessionSettings.bAllowJoinViaPresenceFriendsOnly = false;

		if (Sessions->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), SessionName, SessionSettings)) {
            UE_LOG(LogTemp, Warning, TEXT("Subsystem created"));
        }
        if (Sessions->StartSession(SessionName)) UE_LOG(LogTemp, Warning, TEXT("Start"));
            UGameplayStatics::OpenLevel(WWorld, FName("StartMap") , true, "listen");
        
	}
    else{
        UE_LOG(LogTemp, Warning, TEXT("-vibe"));
    }
}



void ASessionConnect::JoinSession(FName SessionName, ULocalPlayer* LocalPlayer, APlayerController* PlayerController)
{
    PlayerID = 1;
    IOnlineSubsystem* OnlineSub = Online::GetSubsystem(WWorld);
    if (OnlineSub)
    {
        IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
        if (Sessions.IsValid() && LocalPlayer && SessionSearch.IsValid())
        {
            for (int32 SearchIdx = 0; SearchIdx < SessionSearch->SearchResults.Num(); SearchIdx++) {
                FOnlineSessionSearchResult SearchResult = SessionSearch->SearchResults[SearchIdx];
                    FOnlineSessionSettings* SessionSettings = Sessions->GetSessionSettings(SessionName);
                    int PlayersCount = SessionSettings->NumPublicConnections;
                    Sessions->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), FName(*SearchResult.GetSessionIdStr()), SearchResult);
                    FString TravelURL;
                    if (PlayerController && Sessions->GetResolvedConnectString(FName(*SearchResult.GetSessionIdStr()), TravelURL))
                    {
                        PlayerController->ClientTravel(TravelURL, TRAVEL_Absolute);
                    }
            }
        }
    }
}


