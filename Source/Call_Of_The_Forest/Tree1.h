// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "World/StaticWorld.h"
#include "World/AttackedDerivedDeclaration.h"
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

  UPROPERTY()
  AStaticWorld* World; 
  UPROPERTY()
  bool bIsDead;
  UPROPERTY()
  float Health;

  UFUNCTION()
  void Attacked(float Damage)
  {
      Health -= Damage;
      if (Health <= 0)
      {
          bIsDead = true;
      }
  }

    friend class AttackingActor;
    friend class AttackedActor;
  
  public:
  ATree1() {
      TreeComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("tree"));
      ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> TreeAsset(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Sprites/tree_Flipbook.tree_Flipbook'"));
      TreeComponent->SetFlipbook(TreeAsset.Get());
      SetActorScale3D(FVector(0.75, 1.5, 15));
      TreeComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
      TreeComponent->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
      TreeComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
      TreeComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
      TreeComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
      TreeComponent->CanCharacterStepUpOn = ECB_No;
      SetRootComponent(TreeComponent);
      bIsDead = false;
      Health = 100;
      World = AStaticWorld::GetStaticWorld();
  }

  virtual void BeginPlay() override {
      Super::BeginPlay();
      World->AddActor("Tree", this);
  }

  UFUNCTION()
  float GetbIsDead()
  {
      return bIsDead;
  }
};

