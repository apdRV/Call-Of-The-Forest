// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionConnect.h"

// Sets default values
ASessionConnect::ASessionConnect()
{
}

void ASessionConnect::BeginPlay(){
	Super::BeginPlay();
	APlayerController* PlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
	LocalPlayer = PlayerController->GetLocalPlayer();
}

void ASessionConnect::CreateSession(FName SessionName)
{
    IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
	if (Sessions.IsValid() && LocalPlayer)
	{
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = false;
		SessionSettings.bUsesPresence = true;
		SessionSettings.NumPublicConnections = 2;
		SessionSettings.NumPrivateConnections = 0;
		SessionSettings.bAllowInvites = true;
		SessionSettings.bAllowJoinInProgress = true;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bAllowJoinViaPresence = true;
		SessionSettings.bAllowJoinViaPresenceFriendsOnly = false;

		Sessions->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), SessionName, SessionSettings);
	}
}

void ASessionConnect::FindSessions()
{
    IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
    if (OnlineSub)
    {
        IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
        if (Sessions.IsValid() && LocalPlayer)
        {
            SessionSearch = MakeShareable(new FOnlineSessionSearch());
            SessionSearch->bIsLanQuery = false;
            SessionSearch->MaxSearchResults = 20;
            SessionSearch->PingBucketSize = 50;

            Sessions->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), SessionSearch.ToSharedRef());
        }
    }
}

void ASessionConnect::JoinSession(FName SessionName)
{
    IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
    if (OnlineSub)
    {
        IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
        if (Sessions.IsValid() && LocalPlayer && SessionSearch.IsValid())
        {
            for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
            {
                if (SearchResult.GetSessionIdStr().Equals(SessionName.ToString()))
                {
                    Sessions->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), SessionName, SearchResult);
                }
            }
        }
    }
}


