// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Character/MainPaperCharacter.h"
#include "../World/StaticWorld.h"
#include "BehaviorTree/BehaviorTree.h"
#include "MobFlipbookComponent.h"
#include "Components/SphereComponent.h"
#include "PaperCharacter.h"
#include "Mob.generated.h"

/**
 *
 */

UCLASS()
class CALL_OF_THE_FOREST_API AMob : public APaperCharacter {
  GENERATED_BODY()

public:
  AMob();
  virtual void Tick(float Deltatime) override;
  virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

  UFUNCTION()
  float GetSpeed(){
    return Speed;
  }

  UFUNCTION()
  EMobState GetMobState(){
    return MobState;
  }

  UFUNCTION()
  EMobState GetLastMobState(){
    return LastMobState;
  }

  UFUNCTION()
  void SetMobState(EMobState NewState){
      MobState = NewState;
  }
  UFUNCTION(BlueprintCallable, Category = "Trigger")
  bool GetbIsTriggered();

  UFUNCTION(BlueprintCallable, Category = "Trigger")
  void SetbIsTriggered(bool Value);

  UFUNCTION()
  void Attacked(float Value);

  UFUNCTION()
  bool GetbIsDead();

protected:
  virtual void BeginPlay() override;

  UPROPERTY()
  AStaticWorld *World;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
  EMobState MobState;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
  EMobState LastMobState;

  UPROPERTY(EditAnywhere, Category = "State")
  float BaseDamage;

  UPROPERTY(EditAnywhere, Category = "State")
  float Speed;

  UPROPERTY(EditAnywhere, Category = "State")
  float Health;

  UPROPERTY(EditAnywhere, Category = "State")
  bool bIsDead;

  UPROPERTY(EditAnywhere, Category = "State")
  uint8 bIsAttacking;

  UPROPERTY(EditAnywhere, Category = "State")
  bool bIsMoving;

  UPROPERTY()
  bool bIsTriggered;

  UPROPERTY(EditAnywhere, Category = "Health")
  float MaxHealth;

  UFUNCTION(BlueprintCallable, Category = "Movement")
  void MoveForwardBackward(float Value);

  UFUNCTION(BlueprintCallable, Category = "Movement")
  void MoveRightLeft(float Value);

  UFUNCTION(BlueprintCallable, Category = "Attacking")
  void Attack();

  UFUNCTION(BlueprintCallable, Category = "Animation")
  void UpdateMobSprite();

  // properties for animation
  UPROPERTY(EditAnywhere, Category = "Components")
  class UMobFlipbookComponent *MobSpriteComponent;

  UFUNCTION(BlueprintCallable, Category = "State")
  void Die();

private:


};
