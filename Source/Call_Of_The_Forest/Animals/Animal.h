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
	virtual void UpdateAnimalSprite();

	UFUNCTION()
	void UpdateAnimalState();

	UFUNCTION()
  	bool GetbIsActive();

  	UFUNCTION()
  	void SetbIsActive(bool Value);

	UFUNCTION()
	bool GetbIsAttacked();

	UFUNCTION()
	void Attacked(float Value);
	
	UFUNCTION()
	virtual void Die();

	UFUNCTION()
	void SetupOwner(UPaperFlipbookComponent* m_owner);

	UFUNCTION()
	bool GetbIsDead();

	UFUNCTION()
	float GetRadius();

	UFUNCTION()
	void SetRadius(float Value);


protected:
	UPROPERTY()
	EAnimalState AnimalState;

	UPROPERTY()
	EAnimalState LastAnimalState;

	UPROPERTY()
	UPaperFlipbookComponent* AnimalFlipbookComponent;

	UPROPERTY()
	AStaticWorld* World;

	UPROPERTY()
	float Speed;

	UPROPERTY()
	float Health;

	UPROPERTY()
	bool bIsDead;

	UPROPERTY()
	bool bIsAttacked;

	UPROPERTY()
	bool bIsActive;

	UPROPERTY()
	float bRadius;

	UFUNCTION()
	void SetSpeed(float Value);

private:
	
};
