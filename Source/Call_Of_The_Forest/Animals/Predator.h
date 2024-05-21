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
	void Attacked(float Value);

	UFUNCTION()
	virtual void Die();

	UFUNCTION()
	float GetDamage();

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
	float GetRadius();

	UFUNCTION()
	void SetRadius(float Value);

	UFUNCTION()
	void SetSpeed(float Value);

	UFUNCTION()
	EPredatorState GetPredatorState();

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
	float Speed;

	UPROPERTY()
	float Health;

	UPROPERTY()
	float Damage;

	UPROPERTY()
	bool bIsDead;

	UPROPERTY()
	bool bIsAttacking;

	UPROPERTY()
	bool bIsTriggered;

	UPROPERTY()
	bool bIsActive;

	UPROPERTY()
	float bRadius;

	UFUNCTION()
	void Attack();

	UFUNCTION()
	virtual void UpdatePredatorSprite();

	UFUNCTION()
	void SetupOwner(UPaperFlipbookComponent* m_owner);

	UFUNCTION()
	void UpdatePredatorState();

private:
	//Access to protected members for attacking system
	friend class AttackedActor;
	friend class AttackingActor;


};
