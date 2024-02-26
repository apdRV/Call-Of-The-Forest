// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbook.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MainPaperCharacter.generated.h"

UENUM(BlueprintType, Category = "Animation")
enum class EAnimationDirection : uint8
{
	Up,
	Down,
	Left,
	Right,
	UpperLeft,
	UpperRight,
	DownLeft,
	DownRight
};

USTRUCT(BlueprintType, Category = "Animation")
struct FAnimationFlipbooks
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleUp {nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleDown {nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleLeft {nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleRight {nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleUpperLeft {nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleUpperRight{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleDownLeft {nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleDownRight{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* WalkUp {nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* WalkDown {nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* WalkLeft {nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* WalkRight {nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* WalkUpperLeft {nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* WalkUpperRight{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* WalkDownLeft {nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* WalkDownRight{nullptr};

};

/**
 * 
 */

UCLASS()
class CALL_OF_THE_FOREST_API AMainPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	AMainPaperCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health") 
	int Health = 100;

protected:


	// UFUNCTION()
	// virtual void AddMovementInput(FVector WorldDirection, float Scalevalue, bool bForce) override;

	// called when game starts or when spawned
	UFUNCTION()
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationCharacter | Config")
	EAnimationDirection CurrentAnimationDirection {EAnimationDirection::Down};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationCharacter | Config")
	FAnimationFlipbooks Flipbooks;

	// UFUNCTION(BlueprintCallable, Category = "AnimationCharacter")
	// void SetCurrentAnimationDirection(FVector const& Velocity);

	// UFUNCTION(BlueprintCallable, Category = "AnimationCharacter | Animation")
	// void Animate(float DeltaTime, FVector OldLocation, FVector const OldVelocity);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationCharacter | Config")
	bool bIsMoving = true;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};