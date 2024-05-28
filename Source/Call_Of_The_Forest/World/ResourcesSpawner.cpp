// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourcesSpawner.h"
#include "../Enviroment/TreeStump.h"
#include "../Enviroment/Rock.h"
#include "../Enviroment/TreeLog.h"
#include "../Enviroment/SimpleTree.h"
#include "../Enviroment/AppleTree.h"
#include "../Enviroment/Bush.h"

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
EEnviromentObjectType AResourcesSpawner::DetermineObjectType(AActor *Object)
{
	ARock* Rock = dynamic_cast<ARock*>(Object);
	if(Rock != nullptr)
	{
		return EEnviromentObjectType::Rock;
	}

	ABush* Bush = dynamic_cast<ABush*>(Object);
	if(Bush != nullptr)
	{
		return EEnviromentObjectType::Bush;
	} 

	AAppleTree* AppleTree = dynamic_cast<AAppleTree*>(Object);
	if(AppleTree != nullptr)
	{
		return EEnviromentObjectType::AppleTree;
	}

	ASimpleTree* SimpleTree = dynamic_cast<ASimpleTree*>(Object);
	if(SimpleTree != nullptr)
	{
		return EEnviromentObjectType::SimpleTree;
	}

	ATreeLog* TreeLog = dynamic_cast<ATreeLog*>(Object);
	if(Object != nullptr)
	{
		return EEnviromentObjectType::TreeLog;
	}

	ATreeStump* TreeStump = dynamic_cast<ATreeStump*>(Object);
	if(TreeStump != nullptr)
	{
		return EEnviromentObjectType::TreeStump;
	}
	UE_LOG(LogTemp, Warning, TEXT("Incorrect Spawn Object DetermineObjectType"));
	return EEnviromentObjectType::TreeStump; 
}

void AResourcesSpawner::SpawnEnviromentResource(FVector Location, FRotator Rotation, FActorSpawnParameters SpawnParams, EEnviromentObjectType Object)
{
	AResourceBase* ResourceBase = nullptr;
	switch(Object)
	{
		case EEnviromentObjectType::AppleTree:
			ResourceBase = GetWorld()->SpawnActor<AWood>(Location, Rotation, SpawnParams);
			break;
		case EEnviromentObjectType::SimpleTree:
			ResourceBase = GetWorld()->SpawnActor<AWood>(Location, Rotation, SpawnParams);
			break;
		case EEnviromentObjectType::Bush:
			ResourceBase = GetWorld()->SpawnActor<AWood>(Location, Rotation, SpawnParams);
			break;
		case EEnviromentObjectType::Rock:
			ResourceBase = GetWorld()->SpawnActor<AStone>(Location, Rotation, SpawnParams);
			break;
		case EEnviromentObjectType::TreeLog:
			ResourceBase = GetWorld()->SpawnActor<AWood>(Location, Rotation, SpawnParams);
			break;
		case EEnviromentObjectType::TreeStump:
			ResourceBase = GetWorld()->SpawnActor<AWood>(Location, Rotation, SpawnParams);
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Incorrect Type"));
			break;
	}
	if (ResourceBase)
    {
		AASpherePickupActor* SpherePickup = GetWorld()->SpawnActor<AASpherePickupActor>(Location, Rotation, SpawnParams);
		if (SpherePickup)
		{
			SpherePickup->LinkedResource = ResourceBase;
		}
	}

}

void AResourcesSpawner::SpawnResource(FVector Location, FRotator Rotation, FActorSpawnParameters SpawnParams, EResourceType Resource)
{

	AResourceBase* ResourceBase = nullptr;
	switch(Resource)
	{
		case EResourceType::Meat:
			ResourceBase = GetWorld()->SpawnActor<AMeat>(Location, Rotation, SpawnParams);
			break;
		case EResourceType::Stone:
			ResourceBase = GetWorld()->SpawnActor<AStone>(Location, Rotation, SpawnParams);
			break;
		case EResourceType::Trophy:
			ResourceBase = GetWorld()->SpawnActor<ATrophyBase>(Location, Rotation, SpawnParams);
			break;
		case EResourceType::Wood:
			ResourceBase = GetWorld()->SpawnActor<AWood>(Location, Rotation, SpawnParams);
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Incorrect Type"));
			break;
	}

	if (ResourceBase)
    {
		AASpherePickupActor* SpherePickup = GetWorld()->SpawnActor<AASpherePickupActor>(Location, Rotation, SpawnParams);
		if (SpherePickup)
		{
			SpherePickup->LinkedResource = ResourceBase;
		}
	}
}

