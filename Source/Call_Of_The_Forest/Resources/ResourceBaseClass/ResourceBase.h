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


UCLASS()
class CALL_OF_THE_FOREST_API AResourceBase : public APaperFlipbookActor
{
	GENERATED_BODY()

public:	
	AResourceBase();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource")
	class USphereComponent* PickupSphere;

	void OnPickup(class AMainPaperCharacter* Player);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

};
