// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "HobGoblin.generated.h"

UCLASS()
class CALL_OF_THE_FOREST_API AHobGoblin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHobGoblin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "NPC")
	bool isInteracting;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void EnterInteraction();

	UFUNCTION(BlueprintCallable)
	void ExitInteraction();

	UFUNCTION(BlueprintCallable)
	void RunAwayFromHero(ACharacter* Hero){
    if (Hero)
    {
        FVector Direction = GetActorLocation() - Hero->GetActorLocation();
        Direction.Normalize();

        FVector Destination = GetActorLocation() + Direction * 20;
        UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), Destination);
    }
}
};
