// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MainCharacterSpriteComponent.h"
#include "MainPaperCharacter.generated.h"
/**
 * 
 */

UCLASS()
class CALL_OF_THE_FOREST_API AMainPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	AMainPaperCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State") 
	float Health;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationCharacter | Config")
	bool bIsMoving;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationCharacter | Config")
	EMainCharacterState CharacterState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationCharacter | Config")
	EMainCharacterState LastMoveDirection;;

	UFUNCTION()
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "State")
	bool  Die(); // смерть персонажа

	void PickUpItem(float Value); // поднять предмет
    void MoveForwardBackward(float Value);
    void MoveRightLeft(float Value);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class UCameraComponent* FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
    class UMainCharacterSpriteComponent* MainCharacterSpriteComponent;

};