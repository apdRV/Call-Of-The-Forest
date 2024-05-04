// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "../World/StaticWorld.h"
#include "../Character/MainPaperCharacter.h"
#include "Mob.h"
#include "MobAIController.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API AMobAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMobAIController();
protected:
	void BeginPlay() override;
	void Tick(float Delta) override;
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY()
	class AStaticWorld* World;
	UPROPERTY()
	class AMainPaperCharacter *TargetMainCharacter;

private:
	UPROPERTY()
	AMob* m_Mob;

	UFUNCTION(BlueprintCallable, Category = "Moving")
	AMainPaperCharacter* FindTarget();

	UFUNCTION(BlueprintCallable, Category = "Moving")
	void MoveToTarget();
};
