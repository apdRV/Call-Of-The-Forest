// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourcesSpawner.h"

// Sets default values
AResourcesSpawner::AResourcesSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	World = AStaticWorld::GetStaticWorld();

}

// Called when the game starts or when spawned
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

