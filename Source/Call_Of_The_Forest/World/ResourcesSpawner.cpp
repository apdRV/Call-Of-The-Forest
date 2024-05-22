// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourcesSpawner.h"

AResourcesSpawner::AResourcesSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	World = AStaticWorld::GetStaticWorld();

}

void AResourcesSpawner::BeginPlay()
{
	Super::BeginPlay();
	if(World != nullptr)
	{
		World->AddActor("ResourcesSpawner", this);
		UE_LOG(LogTemp, Warning, TEXT("ResourceSpawnerAdded"));
	}
}

void AResourcesSpawner::SpawnResource(FVector Location, FRotator Rotation, FActorSpawnParameters SpawnParams, EResourceType Resource)
{
	switch(Resource)
	{
		case EResourceType::Meat:
			GetWorld()->SpawnActor<AMeat>(Location, Rotation, SpawnParams);
			break;
		case EResourceType::Stone:
			GetWorld()->SpawnActor<AStone>(Location, Rotation, SpawnParams);
			break;
		case EResourceType::Trophy:
			GetWorld()->SpawnActor<ATrophyBase>(Location, Rotation, SpawnParams);
			break;
		case EResourceType::Wood:
			GetWorld()->SpawnActor<AWood>(Location, Rotation, SpawnParams);
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Incorrect Type"));
			break;
	}
}

