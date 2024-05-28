// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "../World/StaticWorld.h"
#include "../World/AttackedDerivedDeclaration.h"
#include "EnviromentObject.generated.h"

/**
 * 
 */
enum class EEnviromentObjectType
{
	Rock,
	Bush,
	AppleTree,
	SimpleTree,
	TreeLog,
	TreeStump
};

UCLASS()
class CALL_OF_THE_FOREST_API AEnviromentObject : public APaperFlipbookActor
{
	GENERATED_BODY()
public:

	AEnviromentObject();

	virtual void BeginPlay() override;

	UFUNCTION()
	bool GetbIsDead();

protected:

	UPROPERTY()
	AStaticWorld* World; 

	UPROPERTY()
	bool bIsDead;

	UPROPERTY()
	float Health;
	
	UFUNCTION()
	void Attacked(float Damage);

private:
    friend class AttackingActor;
    friend class AttackedActor;
};
