// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Multiplayer/SessionConnect.h"
#include "Keeper.generated.h"

UCLASS()
class CALL_OF_THE_FOREST_API AKeeper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeeper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
