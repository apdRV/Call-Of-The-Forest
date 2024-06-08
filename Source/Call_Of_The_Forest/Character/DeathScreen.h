// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainPaperCharacter.h"
#include "../World/StaticWorld.h"
#include "Kismet/GameplayStatics.h"
#include "DeathScreen.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API UDeathScreen : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere)
	AMainPaperCharacter* Player;

	UFUNCTION(BlueprintCallable)
	bool getDiedState(){
		Player = Cast<AMainPaperCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Player){
			return Player->GetbIsDead();
		}
		return false;
	}
	
};
