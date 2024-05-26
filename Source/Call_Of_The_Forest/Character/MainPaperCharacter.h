// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
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

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	AMainPaperCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleANywhere, BlueprintReadOnly, Category = "Resource")
	class USphereComponent* InteractionSphere;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State") 
	float Health;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationCharacter | Config")
	bool bIsMoving;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	uint8 bIsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationCharacter | Config")
	EMainCharacterState CharacterState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationCharacter | Config")
	EMainCharacterState LastMoveDirection;;

	UFUNCTION()
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "State")
	void Die(); // смерть персонажа

	UFUNCTION(BlueprintCallable, Category = "Movement")
    void MoveForwardBackward(float Value);

	UFUNCTION(BlueprintCallable, Category = "Movement")
    void MoveRightLeft(float Value);

	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void Attack();

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void UpdateCharacterSprite();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class UCameraComponent* FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
    class UMainCharacterSpriteComponent* MainCharacterSpriteComponent;

};