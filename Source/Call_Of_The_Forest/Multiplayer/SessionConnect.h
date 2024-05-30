// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OnlineSessionSettings.h"
#include "Engine/World.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Kismet/GameplayStatics.h"
#include "SessionConnect.generated.h"

UCLASS()
class CALL_OF_THE_FOREST_API ASessionConnect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASessionConnect();
	ULocalPlayer* LocalPlayer;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	void JoinSession(FName SessionName);
	void CreateSession(FName SessionName);
	void FindSessions();
};
