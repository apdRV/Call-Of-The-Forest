// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Tree1.generated.h"


/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API ATree1: public APaperFlipbookActor
{
  GENERATED_BODY()
  UPROPERTY(VisibleAnywhere, Category=paper)
  UPaperFlipbookComponent* TreeComponent;

  public:
  ATree1(){
    TreeComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("tree"));
    ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> TreeAsset(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Spawners/Tree/depressed_tree.depressed_tree'"));
    TreeComponent->SetFlipbook(TreeAsset.Get());
    SetRootComponent(TreeComponent);
  }

  virtual void BeginPlay() override {
    Super::BeginPlay();
    SetActorScale3D(FVector(0.5, 1, 0.4));
  }
};

