// Fill out your copyright notice in the Description page of Project Settings.

#include "Generator.h"

// Sets default values
AGenerator::AGenerator() {
  // Set this actor to call Tick() every frame.  You can turn this off to
  // improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
  start = std::chrono::steady_clock::now();
  ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystemObj(
      TEXT("/Script/Niagara.NiagaraSystem'/Game/Weather/NG_Rain.NG_Rain'"));
  Rain = NiagaraSystemObj.Object;
}

// Called when the game starts or when spawned
void AGenerator::BeginPlay() { Super::BeginPlay(); }

// Called every frame
void AGenerator::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);
  end = std::chrono::steady_clock::now();
  std::chrono::duration<int> elapsed =
      std::chrono::duration_cast<std::chrono::seconds>(end - start);
  if (elapsed.count() >= 10){
   r start = std::chrono::steady_clock::now();
    random_num--;
    if (!is_rain) {
      if (std::rand() % 100 >= random_num) {
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(), Rain, FVector(0, 0, 10), FRotator(0, 180, 0),
            FVecto(1, 1, 1), true, true, ENCPoolMethod::None, true);
        random_num = 100;
      }
    }
    else {
      if (std::rand() % 100 >= random_num) {
        CurrentRain->DestroyComponent();
        random_num = 100;
      }
    }
  }
}
