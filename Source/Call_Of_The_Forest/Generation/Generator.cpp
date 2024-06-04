// Fill out your copyright notice in the Description page of Project Settings.

#include "Generator.h"
#include "Net/UnrealNetwork.h"

AGenerator::AGenerator() {
  PrimaryActorTick.bCanEverTick = true;
  start = std::chrono::steady_clock::now();
  ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystemObj(
      TEXT("/Script/Niagara.NiagaraSystem'/Game/Weather/NG_Rain.NG_Rain'"));
  Rain = NiagaraSystemObj.Object;

  bReplicates = true;

  bAlwaysRelevant = true;

  is_spawned = false;
  is_destroyed = true;
  is_rain = false;

}

void AGenerator::BeginPlay() { 
  Super::BeginPlay();
}

void AGenerator::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
  Super::GetLifetimeReplicatedProps(OutLifetimeProps);

  DOREPLIFETIME(AGenerator, is_rain);
  DOREPLIFETIME(AGenerator, is_spawned);
  DOREPLIFETIME(AGenerator, is_destroyed);
}

void AGenerator::Tick(float DeltaTime) 
{
  Super::Tick(DeltaTime);
  SetServerState();
}

void AGenerator::SetRain()
{
  if (is_rain && !is_spawned) {
    if(HasAuthority())
    {
      UE_LOG(LogTemp, Warning, TEXT("Called rain on server"));
    }
    else
    {
      UE_LOG(LogTemp, Warning, TEXT("Called rain on client"));
    }
  UNiagaraFunctionLibrary::SpawnSystemAtLocation(
      GetWorld(), Rain, FVector(0, 0, 10), FRotator(0, 180, 0),
      FVector(1, 1, 1), true, true, ENCPoolMethod::None, true);
      if (HasAuthority()){
        ServerSet_is_spawned(true);
        ServerSet_is_destroyed(false);
      }
  }
  if (!is_rain && !is_destroyed) {
    if(HasAuthority())
    {
      UE_LOG(LogTemp, Warning, TEXT("Called rain end on server"));
    }
    else
    {
      UE_LOG(LogTemp, Warning, TEXT("Called rain end on client"));
    }
    if(CurrentRain){
      CurrentRain->DestroyComponent();
    }
    if(HasAuthority()){
      ServerSet_is_destroyed(true);
      ServerSet_is_spawned(false);
    }
  } 

}


void AGenerator::SetServerState()
{
    end = std::chrono::steady_clock::now();
    std::chrono::duration<int> elapsed =
        std::chrono::duration_cast<std::chrono::seconds>(end - start);
    if (elapsed.count() >= 10) {
      start = std::chrono::steady_clock::now();
      random_num--;
      if (!is_rain) {
        if (std::rand() % 100 >= random_num) {
          if (HasAuthority()){
            ServerSet_is_rain(true);
          }
          random_num = 100;
        }
      } 
      else {
        if (std::rand() % 100 >= random_num) {
          if (HasAuthority()){
            ServerSet_is_rain(false);
          }
          random_num = 100;
        }
      }
    }
}

void AGenerator::OnRep_is_rain()
{
  SetRain();
  // UE_LOG(LogTemp, Warning, TEXT("Called OnRep_is_rain"));
}

void AGenerator::OnRep_is_spawned()
{
  SetRain();
  // UE_LOG(LogTemp, Warning, TEXT("Called OnRep_is_spawned"));
}

void AGenerator::OnRep_is_destroyed()
{
  SetRain();
  // UE_LOG(LogTemp, Warning, TEXT("Called OnRep_is_destroyed"));
}

void AGenerator::ServerSet_is_rain_Implementation(bool Value)
{
  if(is_rain != Value){
    is_rain = Value;
    MulticastSetRain(is_rain);
  }
}

bool AGenerator::ServerSet_is_rain_Validate(bool Value)
{
  return true;
}

void AGenerator::ServerSet_is_spawned_Implementation(bool Value)
{
  if(is_spawned != Value)
  {
    is_spawned = Value;
  }
}

bool AGenerator::ServerSet_is_spawned_Validate(bool Value)
{
  return true;
}

void AGenerator::ServerSet_is_destroyed_Implementation(bool Value)
{
  if(is_destroyed != Value)
  {
    is_destroyed = Value;
  }
}

bool AGenerator::ServerSet_is_destroyed_Validate(bool Value)
{
  return true;
}

void AGenerator::MulticastSetRain_Implementation(bool bIsRaining)
{
    is_rain = bIsRaining;
    SetRain();
}
