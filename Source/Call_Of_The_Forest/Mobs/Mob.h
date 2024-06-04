// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Character/MainPaperCharacter.h"
#include "../World/StaticWorld.h"
#include "BehaviorTree/BehaviorTree.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbook.h"
#include "Engine/World.h"
#include "Components/SphereComponent.h"
#include "PaperCharacter.h"
#include "../World/AttackedDerivedDeclaration.h"
#include "Engine/EngineTypes.h"
#include "Net/UnrealNetwork.h"
#include "Mob.generated.h"

/**
 *
 */
UENUM(BlueprintType, Category = "State")
enum class EMobState : uint8{
	LeftDown,
	RightUp,
	IdleLeftDown,
	IdleRightUp,
	AttackLeftDown,
	AttackRightUp,
	DieLeftDown,
	DieRightUp
};


UCLASS()
class CALL_OF_THE_FOREST_API AMob : public APaperCharacter {
  GENERATED_BODY()

public:
  AMob();
  virtual void Tick(float Deltatime) override;
  virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
  virtual void BeginPlay() override;

  UFUNCTION()
  float GetSpeed();

  UFUNCTION()
  EMobState GetMobState();

  UFUNCTION()
  EMobState GetLastMobState();

  UFUNCTION()
  void SetMobState(EMobState NewState);

  UFUNCTION()
  void SetLastMobState(EMobState NewState);
  
  UFUNCTION(BlueprintCallable, Category = "Trigger")
  bool GetbIsTriggered();

  UFUNCTION(BlueprintCallable, Category = "Trigger")
  void SetbIsTriggered(bool Value);

  UFUNCTION()
  bool GetbIsDead();

  UFUNCTION()
  void SetSpeed(float Value);

  UFUNCTION()
  float GetRadius();

  UFUNCTION()
  void SetRadius(float Value);

  UFUNCTION()
  float GetBaseDamage();

  UFUNCTION()
  bool GetbIsDestroyed();

  UFUNCTION()
  void SetbIsDestroyed(bool Value);

protected:

	//for server 	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

  UFUNCTION()
  void Attacked(float Value);

	UFUNCTION()
	void SetupOwner(UPaperFlipbookComponent* m_owner);
  
  UPROPERTY()
  AStaticWorld *World;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category = "AnimationCharacter | Config")
  EMobState MobState;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "AnimationCharacter | Config")
  EMobState LastMobState;

  UPROPERTY(EditAnywhere, Replicated,  Category = "State")
  float BaseDamage;

  UPROPERTY(EditAnywhere, Category = "State")
  float Speed;

  UPROPERTY(EditAnywhere, Replicated, Category = "State")
  float Health;

  UPROPERTY(EditAnywhere, Replicated, Category = "State")
  bool bIsDead;

  UPROPERTY(EditAnywhere, Category = "State")
  bool bIsAttacking;

  UPROPERTY(EditAnywhere, Category = "State")
  bool bIsMoving;

  UPROPERTY()
  bool bIsTriggered;

  UPROPERTY()
  bool bIsDestroyed;

  UPROPERTY(EditAnywhere, Category = "Health")
  float MaxHealth;

  UPROPERTY()
  float bRadius;

  UFUNCTION(BlueprintCallable, Category = "Movement")
  void MoveForwardBackward(float Value);

  UFUNCTION(BlueprintCallable, Category = "Movement")
  void MoveRightLeft(float Value);

  UFUNCTION(BlueprintCallable, Category = "Attacking")
  void Attack();

  UFUNCTION(BlueprintCallable, Category = "Animation")
  void UpdateMobState();

  UFUNCTION()
  virtual void UpdateMobSprite();

  UFUNCTION()
  virtual void SetMobSprite(EMobState NewMobState);

  UFUNCTION()
  void SetAttackAnimation();

  UFUNCTION()
  void EndAttackAnimation();

	UPROPERTY()
  FTimerHandle AttackTimerHandle;

	UPROPERTY()
	UPaperFlipbookComponent* MobFlipbookComponent;

  UFUNCTION(BlueprintCallable, Category = "State")
  void Die();


private:
	//Access to protected members for attacking system
	friend class AttackedActor;
  
	friend class AttackingActor;

};
