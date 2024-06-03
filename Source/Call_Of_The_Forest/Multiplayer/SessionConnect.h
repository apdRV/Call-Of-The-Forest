// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "../Database/MyDatabase.h"
#include "Engine/World.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Kismet/GameplayStatics.h"
#include "SessionConnect.generated.h"


class CALL_OF_THE_FOREST_API UJoinSession;

UCLASS()
class CALL_OF_THE_FOREST_API ASessionConnect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASessionConnect();
	~ASessionConnect();
	static UWorld* WWorld;
	static int PlayerID;
	static ASessionConnect* CurrentSession;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	virtual void BeginPlay() override;
	static int GetID();
	static void SetWorld(UWorld* World);
	void JoinSession(FName SessionName, ULocalPlayer* LocalPlayer, APlayerController* PlayerController);
	void CreateSession(FName SessionName, ULocalPlayer* LocalPlayer, APlayerController* PlayerController);
	TSharedPtr<FOnlineSessionSearch> FindSessions(ULocalPlayer* LocalPlayer);
	static ASessionConnect* GetCurrentSession();
};
