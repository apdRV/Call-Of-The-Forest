// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "MobsAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "../Character/MainPaperCharacter.h"
#include "MobSpriteComponent.h"
#include "Mob.generated.h"

/**
 * 
 */

UCLASS()
class CALL_OF_THE_FOREST_API AMob : public APaperCharacter
{
	GENERATED_BODY()

public:
	AMob();
	virtual void Tick(float Deltatime) override;

	UBehaviorTree* GetBehaviourTree() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	EMobState MobState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	EMobState LastMobState;

	UPROPERTY(EditAnywhere, Category = "State")
	float BaseDamage;

	UPROPERTY(EditAnywhere, Category = "State")
	float Health;

	UPROPERTY(EditAnywhere, Category = "State")
	bool bIsDead;

	UPROPERTY(EditAnywhere, Category = "State")
	uint8 bIsAttacking;

	UPROPERTY(EditAnywhere, Category = "State")
	bool bIsMoving;

	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth;



	// properties for animation
	UPROPERTY(EditAnywhere, Category =  "Components")
	class UMobSpriteComponent *MobSpriteComponent;
	


	// Properties for AI

	class UMainPaperCharacter *MainCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* Tree;


	UFUNCTION(BlueprintCallable, Category = "Animation")
	void UpdateMobSprite();


	UFUNCTION(BlueprintCallable, Category = "State")
	void Die();

};
