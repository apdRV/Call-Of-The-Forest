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
#include "Animal.generated.h"

/**
 * 
 */
UENUM(BlueprintType, Category = "Animation")
enum class EAnimalState : uint8{
	LeftDown,
	RightUp,
	IdleLeftDown,
	IdleRightUp,
	DieLeftDown,
	DieRightUp
};

UCLASS()
class CALL_OF_THE_FOREST_API AAnimal : public APaperCharacter
{
	GENERATED_BODY()
public:

	AAnimal();

	UFUNCTION()
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void BeginPlay() override;

	UFUNCTION()
  	bool GetbIsActive();

  	UFUNCTION()
  	void SetbIsActive(bool Value);

	UFUNCTION()
	bool GetbIsAttacked();

	UFUNCTION()
	bool GetbIsDead();

	UFUNCTION()
	float GetbRadius();

	UFUNCTION()
	void SetbRadius(float Value);

	UFUNCTION()
	void SetbSpeed(float Value);

	UFUNCTION()
	bool GetbIsDestroyed();

	UFUNCTION()
	void SetbIsDestroyed(bool Value);

	UFUNCTION()
	void SetupOwner(UPaperFlipbookComponent* bOwner);

protected:

	UPROPERTY()
	EAnimalState AnimalState;

	UPROPERTY()
	EAnimalState LastAnimalState;

	UPROPERTY()
	float bSpeed;

	UPROPERTY()
	float bHealth;

	UPROPERTY()
	bool bIsDead;

	UPROPERTY()
	bool bIsAttacked;

	UPROPERTY()
	bool bIsActive;

	UPROPERTY()
	bool bIsDestroyed;

	UPROPERTY()
	float bRadius;

	UPROPERTY()
	UPaperFlipbookComponent* AnimalFlipbookComponent;

	UPROPERTY()
	AStaticWorld* World;

	UFUNCTION()
	void UpdateAnimalState();

	UFUNCTION()
	virtual void UpdateAnimalSprite();

	UFUNCTION()
	void Attacked(float Value);

	UFUNCTION()
	virtual void Die();

private:

	//Access to protected members for attacking system
	friend class AttackedActor; 
	
	friend class AttackingActor;
};
