// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ResourceBaseClass/ResourceBase.h"
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
    class AResourceBase* CurrentInteractable;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    TArray<AResourceBase*> Inventory;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    int32 Money;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 InventorySlotLimit;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 InventoryWeightLimit;

protected:
    void Interact();

    virtual void SetupInputComponent() override;
};
