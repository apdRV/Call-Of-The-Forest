// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MobsAIController.generated.h"



/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API AMobsAIController : public AAIController
{
	GENERATED_BODY()
public:
	explicit AMobsAIController(FObjectInitializer const& ObjectInitializer);
protected:
	virtual void OnPossess(APawn* InPawn) override;
};
