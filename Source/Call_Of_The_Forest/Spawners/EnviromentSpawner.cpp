// Fill out your copyright notice in the Description page of Project Settings.


#include "EnviromentSpawner.h"
#include "../Enviroment/Rock.h"
#include "../Enviroment/SimpleTree.h"
#include "../Enviroment/Bush.h"
#include "../Enviroment/AppleTree.h"
#include "../Enviroment/TreeLog.h"
#include "../Enviroment/TreeStump.h"
#include "Net/UnrealNetwork.h"
#include "Math/UnrealMathUtility.h"

AEnviromentSpawner::AEnviromentSpawner()
{

	PrimaryActorTick.bCanEverTick = false;

}

void AEnviromentSpawner::BeginPlay()
{
	Super::BeginPlay();
    if(HasAuthority()){
        SpawnEnviromentObject();
    }

	
}

EEnviromentObjectType AEnviromentSpawner::GenerateRandomObject()
{
    int32 EnviromentObjectType = FMath::RandRange(1, 6);
    switch(EnviromentObjectType)
    {
        case 1:
            return EEnviromentObjectType::Rock;
            break;
        case 2:
            return EEnviromentObjectType::Bush;
            break;
        case 3:
            return EEnviromentObjectType::AppleTree;
            break;
        case 4:
            return EEnviromentObjectType::TreeLog;
            break;
        case 5:
            return EEnviromentObjectType::TreeStump;
            break;
        default:
            return EEnviromentObjectType::SimpleTree;
            break;
    }

}

void AEnviromentSpawner::SpawnEnviromentObject()
{
    FRotator Rotation(0, -90, 90);
    for (int l = -7; l < 7; l++) {
        for (int r = -7; r < 7; r++) {
            for (int i = 0; i < 3; i++) {
                FVector Location = { 0, 0, 13 };
                Location[0] = l * 500 + FMath::RandRange(0, 500);
                Location[1] = r * 500 + FMath::RandRange(0, 500);
                if(FMath::Abs(Location[0]) < 100.0f || FMath::Abs(Location[1]) < 100.0f)
                {
                    continue;
                }
                switch(GenerateRandomObject())
                {
                    case EEnviromentObjectType::Rock:
                        {
                            GetWorld()->SpawnActor<ARock>(Location, Rotation);
                        }
                        break;
					case EEnviromentObjectType::Bush:
						{
							GetWorld()->SpawnActor<ABush>(Location, Rotation);
						}
						break;
					case EEnviromentObjectType::AppleTree:
						{
							GetWorld()->SpawnActor<AAppleTree>(Location, Rotation);
						}
						break;
					case EEnviromentObjectType::SimpleTree:
						{
							GetWorld()->SpawnActor<ASimpleTree>(Location, Rotation);
						}
						break;
                    case EEnviromentObjectType::TreeLog:
                        {
                            GetWorld()->SpawnActor<ATreeLog>(Location, Rotation);
                        }
                        break;
                    case EEnviromentObjectType::TreeStump:
                        {
                            GetWorld()->SpawnActor<ATreeStump>(Location, Rotation);
                        }
                        break;
                }
            }
        }
    }
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
}