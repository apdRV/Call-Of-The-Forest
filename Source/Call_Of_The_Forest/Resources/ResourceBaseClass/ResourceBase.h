// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
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
class CALL_OF_THE_FOREST_API AResourceBase : public APaperSpriteActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Trigger)
	class UCapsuleComponent* TriggerCapsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Tooltip)
	class UTextRenderComponent* Tooltip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	FResourceData Data;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPaperFlipbook* ResourceBaseFlipbook{nullptr};

};
