// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Resources/ResourceBaseClass/ResourceBase.h"
#include "InventoryItem.h"
#include "GameFramework/PlayerController.h"
#include "InventoryController.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API AInventoryController : public APlayerController
{
	GENERATED_BODY()

public:
    AInventoryController();

    UFUNCTION(BlueprintImplementableEvent)
    void ReloadInventory();

    UFUNCTION(BlueprintCallable, Category = "Utils")
    bool AddItemToInventoryByID(FName ID);

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    TArray<FInventoryItem> Inventory;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    int32 Wood;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    int32 Meat;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    int32 Stone;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    int32 Throphy;

protected:
    void Interact();

    virtual void SetupInputComponent() override;
};
