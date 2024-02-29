// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbook.h"
#include "Tree1.generated.h"


/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API ATree1 : public APaperFlipbookActor
{
	GENERATED_BODY()
	public:
	UPROPERTY()
	UPaperFlipbook* myFlipbook;
	void BeginPlay(){
		Super::BeginPlay();
		myFlipbook = LoadObject<UPaperFlipbook>(nullptr, TEXT("/Script/Paper2D.PaperFlipbook'/Game/Spawners/Tree/depressed_tree.depressed_tree'"));
	}
};
