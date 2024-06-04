// Fill out your copyright notice in the Description page of Project Settings.


#include "DayNightCycle.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ADayNightCycle::ADayNightCycle()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	bAlwaysRelevant = true;

}

// Called when the game starts or when spawned
void ADayNightCycle::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority()) {
		TimeOfDay = 80.0f;
	}
	
}

void ADayNightCycle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADayNightCycle, TimeOfDay);
}

// Called every frame
void ADayNightCycle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateTimeOfDay(DeltaTime);
}

void ADayNightCycle::OnRep_TimeOfDay()
{
	UpdateLighting();
}

void ADayNightCycle::ServerSetTimeOfDay_Implementation(float NewTimeOfDay)
{
	TimeOfDay = NewTimeOfDay;
}

bool ADayNightCycle::ServerSetTimeOfDay_Validate(float NewTimeOfDay)
{
	return true;
}

void ADayNightCycle::UpdateTimeOfDay(float DeltaTime)
{
	TimeOfDay += DeltaTime;
	if (TimeOfDay >= 120.0f) { 
		TimeOfDay -= 120.0f;
	}
	if(HasAuthority()){
		ServerSetTimeOfDay(TimeOfDay);
	}
	UpdateLighting();
}

void ADayNightCycle::UpdateLighting()
{
	if (lightSource){
		lightSource->SetActorRotation(FRotator((TimeOfDay * turnRate), 0, 0));
	}
	if (sun){
		FOutputDeviceNull ar;
		sun->CallFunctionByNameWithArguments(TEXT("UpdateSunDirection"), ar, NULL, true);
	}
}
