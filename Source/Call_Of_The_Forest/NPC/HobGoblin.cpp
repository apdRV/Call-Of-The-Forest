// Fill out your copyright notice in the Description page of Project Settings.


#include "HobGoblin.h"

// Sets default values
AHobGoblin::AHobGoblin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isInteracting = false;

}

// Called when the game starts or when spawned
void AHobGoblin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHobGoblin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHobGoblin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHobGoblin::EnterInteraction(){
	isInteracting = true;
}

void AHobGoblin::ExitInteraction(){
	isInteracting = false;
}

