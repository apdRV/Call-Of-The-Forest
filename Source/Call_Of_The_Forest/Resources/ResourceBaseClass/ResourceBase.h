// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "ResourceBase.generated.h"

UCLASS()
class CALL_OF_THE_FOREST_API AResourceBase : public APaperSpriteActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPaperFlipbook* ResourceBaseFlipbook{nullptr};

};
