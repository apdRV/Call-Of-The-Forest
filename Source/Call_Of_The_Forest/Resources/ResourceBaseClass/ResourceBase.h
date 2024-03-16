// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include "ResourceBase.generated.h"

USTRUCT(BlueprintType)
struct FResourceData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<AResourceBase> Class;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UPaperSprite* Image{nullptr};

	UPROPERTY(BlueprintReadOnly)
	FString Name;

};

UCLASS()
class CALL_OF_THE_FOREST_API AResourceBase : public APaperFlipbookActor
{
	GENERATED_BODY()

public:	
	AResourceBase(){

	Name = "Interactable";
	Action = "Interact";
	};

	UFUNCTION(BlueprintNativeEvent)
	void Interact(APlayerController* Controller);
	virtual void Interact_Implementation(APlayerController* Controller);

	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	FString Action;

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	FString GetInteractText() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Trigger)
	class UCapsuleComponent* TriggerCapsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Tooltip)
	class UTextRenderComponent* Tooltip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	FResourceData Data;

};
