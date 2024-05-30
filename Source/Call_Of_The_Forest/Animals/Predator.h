// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbook.h"
#include "GameFramework/Character.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../World/StaticWorld.h"
#include "../World/AttackedDerivedDeclaration.h"
#include "Engine/EngineTypes.h"
#include "Predator.generated.h"

/**
 * 
 */
UENUM(BlueprintType, Category = "Animation")
enum class EPredatorState : uint8{
	LeftDown,
	RightUp,
	IdleLeftDown,
	IdleRightUp,
	AttackingLeftDown,
	AttackingRightUp,
	HitLeftDown,
	HitRightUp,
	DieLeftDown,
	DieRightUp
};
UCLASS()
class CALL_OF_THE_FOREST_API APredator : public APaperCharacter
{
	GENERATED_BODY()

public:
	APredator();

	UFUNCTION()
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void BeginPlay() override;

	UFUNCTION()
	float GetbDamage();

	UFUNCTION()
  	bool GetbIsActive();

  	UFUNCTION()
  	void SetbIsActive(bool Value);

	UFUNCTION()
	bool GetbIsTriggered();

	UFUNCTION()
	void SetbIsTriggered(bool Value);

	UFUNCTION()
	bool GetbIsDead();

	UFUNCTION()
	float GetbRadius();

	UFUNCTION()
	void SetbRadius(float Value);

	UFUNCTION()
	void SetbSpeed(float Value);

	UFUNCTION()
	EPredatorState GetPredatorState();

	UFUNCTION()
	bool GetbIsDestroyed();

	UFUNCTION()
	void SetbIsDestroyed(bool Value);

	UFUNCTION()
	void SetPredatorState(EPredatorState NewState);

protected:
	UPROPERTY()
	EPredatorState PredatorState;

	UPROPERTY()
	EPredatorState LastPredatorState;

	UPROPERTY()
	UPaperFlipbookComponent* PredatorFlipbookComponent;

	UPROPERTY()
	AStaticWorld* World;

	UPROPERTY()
	float bSpeed;

	UPROPERTY()
	float bHealth;

	UPROPERTY()
	float bDamage;

	UPROPERTY()
	bool bIsDead;

	UPROPERTY()
	bool bIsAttacking;

	UPROPERTY()
	bool bIsDestroyed;

	UPROPERTY()
	FTimerHandle AttackTimerHandle;

	UPROPERTY()
	bool bIsTriggered;

	UPROPERTY()
	bool bIsActive;

	UPROPERTY()
	float bRadius;

	UFUNCTION()
	void Attacked(float Value);

	UFUNCTION()
	void SetAttackAnimation();

	UFUNCTION()
	void EndAttackAnimation();

	UFUNCTION()
	virtual void UpdatePredatorSprite();

	UFUNCTION()
	void UpdatePredatorState();

	UFUNCTION()
	void SetupOwner(UPaperFlipbookComponent* m_owner);
	
	UFUNCTION()
	virtual void Die();

private:
	//Access to protected members for attacking system
	friend class AttackedActor;
	friend class AttackingActor;


};
