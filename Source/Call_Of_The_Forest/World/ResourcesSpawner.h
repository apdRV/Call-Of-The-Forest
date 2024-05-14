// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Resources/Meat/Meat.h"
#include "../Resources/ResourceBaseClass/ResourceBase.h"
#include "../Resources/Stone/Stone.h"
#include "../Resources/Trophy/TrophyBase.h"
#include "../Resources/Wood/Wood.h"
#include "StaticWorld.h"
#include "ResourcesSpawner.generated.h"

enum class EResourceType{
	Meat,
	Stone,
	Trophy,
	Wood
};

UCLASS()
class CALL_OF_THE_FOREST_API AResourcesSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourcesSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SpawnResource(FVector Location, FRotator Rotation, FActorSpawnParameters SpawnParams, EResourceType Resource);

	UPROPERTY()
	AStaticWorld* World;

};
