// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
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

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category =  "Components")
	class UMobSpriteComponent *MobSpritel;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float BaseDamage;

	UPROPERTY(EditAnywhere, Category = "Health")
	float Health;

	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth;
	class UMainPaperCharacter *MainCharacter;

};
