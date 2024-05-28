// Fill out your copyright notice in the Description page of Project Settings.


#include "EnviromentObject.h"

AEnviromentObject::AEnviromentObject()
{
    PrimaryActorTick.bCanEverTick = true;
    bIsDead = false;
    Health = 100;
    World = AStaticWorld::GetStaticWorld();
}

void AEnviromentObject::BeginPlay()
{
    Super::BeginPlay();
    if(World != nullptr)
    {
        World->AddActor("EnviromentObject", this);
    }
}

bool AEnviromentObject::GetbIsDead()
{
    return bIsDead;
}

void AEnviromentObject::Attacked(float Damage)
{
    UE_LOG(LogTemp, Warning, TEXT("Enviroment Attacked called"));
    Health -= Damage;
    if (Health <= 0)
    {
        bIsDead = true;
    }
}