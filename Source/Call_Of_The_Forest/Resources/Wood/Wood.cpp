// Fill out your copyright notice in the Description page of Project Settings.

#include "Wood.h"

// Sets default values
AWood::AWood()
{
 	Quantity = 1 + std::rand() % 10; 
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWood::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

