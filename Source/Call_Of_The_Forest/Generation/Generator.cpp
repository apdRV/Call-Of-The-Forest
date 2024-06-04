// Fill out your copyright notice in the Description page of Project Settings.

#include "Generator.h"

AGenerator::AGenerator() {
  PrimaryActorTick.bCanEverTick = true;
  start = std::chrono::steady_clock::now();
  ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystemObj(
      TEXT("/Script/Niagara.NiagaraSystem'/Game/Weather/NG_Rain.NG_Rain'"));
  Rain = NiagaraSystemObj.Object;
}

void AGenerator::BeginPlay() { Super::BeginPlay(); }

void AGenerator::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);
  if (HasAuthority()){
    end = std::chrono::steady_clock::now();
    std::chrono::duration<int> elapsed =
        std::chrono::duration_cast<std::chrono::seconds>(end - start);
    if (elapsed.count() >= 10) {
      start = std::chrono::steady_clock::now();
      random_num--;
      if (!is_rain) {
        if (std::rand() % 100 >= random_num) {
          is_rain = true;
          random_num = 100;
        }
      } 
      else {
        if (std::rand() % 100 >= random_num) {
          is_rain = false;
          random_num = 100;
        }
      }
    }
  }
  if (is_rain && !is_spawned) {
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(), Rain, FVector(0, 0, 10), FRotator(0, 180, 0),
        FVector(1, 1, 1), true, true, ENCPoolMethod::None, true);
    is_spawned = true;
    is_destroyed = false;
  }
  if (!is_rain && !is_destroyed) {
    CurrentRain->DestroyComponent();
    is_destroyed = true;
    is_spawned = false;
  }
}
