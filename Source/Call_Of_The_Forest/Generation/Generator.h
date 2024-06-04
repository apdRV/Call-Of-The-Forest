// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <chrono>
#include <cstdlib>
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Generator.generated.h"

UCLASS()
class CALL_OF_THE_FOREST_API AGenerator : public AActor
{
    GENERATED_BODY()
    
public: 
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;

    UPROPERTY(ReplicatedUsing = OnRep_is_rain)
    bool is_rain;

    UPROPERTY(ReplicatedUsing = OnRep_is_spawned)
    bool is_spawned;

    UPROPERTY(ReplicatedUsing = OnRep_is_destroyed)
    bool is_destroyed;

    int random_num = 100;

    UPROPERTY()
    UNiagaraSystem* Rain;

    UPROPERTY()
    UNiagaraComponent* CurrentRain;
    // Sets default values for this actor's properties
    AGenerator();

protected:

    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION()
    void OnRep_is_rain();

    UFUNCTION()
    void OnRep_is_spawned();

    UFUNCTION()
    void OnRep_is_destroyed();

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerSet_is_rain(bool Value);

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerSet_is_spawned(bool Value);

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerSet_is_destroyed(bool Value);

    UFUNCTION(NetMulticast, Reliable)
    void MulticastSetRain(bool bIsRaining);

    UFUNCTION()
    void SetRain();

    UFUNCTION()
    void SetServerState();

public: 

    virtual void Tick(float DeltaTime) override;

};

