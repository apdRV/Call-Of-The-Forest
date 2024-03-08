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
	// Sets default values for this actor's properties
	AResourceBase(){
	// 	TriggerCapsule = CreateDefaultSubobject<class UCapsuleComponent>("Trigger capsule");

	// Tooltip = CreateDefaultSubobject<class UTextRenderComponent>("Tooltip");
	// Tooltip->SetupAttachment(RootComponent);
	// Tooltip->SetAbsolute(false, true, true);
	// Tooltip->SetRelativeLocation(FVector(0.0f, 200.0f, 10.0f));
	// Tooltip->SetRelativeRotation(FRotator(90.0f, 180.0f, 0.0f));
	// Tooltip->SetWorldScale3D(FVector(1.0f, 0.15f, 0.15f));
	// Tooltip->SetHorizontalAlignment(EHTA_Center);
	// Tooltip->SetVerticalAlignment(EVRTA_TextBottom);
	// Tooltip->SetText(FText::FromString("Press E to take"));
	// Tooltip->SetTextRenderColor(FColor(255, 122, 0, 255));
	// Tooltip->SetHiddenInGame(true);
	// Tooltip->SetIsReplicated(true);

	// GetRenderComponent()->SetMobility(EComponentMobility::Movable);
	// GetRenderComponent()->SetSimulatePhysics(true);
	// GetRenderComponent()->SetEnableGravity(true);
	// GetRenderComponent()->SetConstraintMode(EDOFMode::Type::Default);
	// GetRenderComponent()->GetBodyInstance()->bLockXRotation = true;
	// GetRenderComponent()->GetBodyInstance()->bLockYRotation = true;
	// GetRenderComponent()->GetBodyInstance()->MassScale = 500.0f;
	// GetRenderComponent()->CanCharacterStepUpOn = ECB_No;
	// GetRenderComponent()->SetIsReplicated(true);

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
