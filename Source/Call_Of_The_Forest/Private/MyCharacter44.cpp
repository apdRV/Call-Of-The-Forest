// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter44.h"

// Sets default values
AMyCharacter44::AMyCharacter44()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter44::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter44::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter44::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

