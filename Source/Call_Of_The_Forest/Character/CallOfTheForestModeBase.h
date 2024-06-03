// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../Mobs/Mob.h"
#include "../Multiplayer/SessionConnect.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "CallOfTheForestModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API ACallOfTheForestModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ACallOfTheForestModeBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemies, meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AMob> SkeletonClass;


};
