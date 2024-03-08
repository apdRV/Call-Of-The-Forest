// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "InventoryItem.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CALL_OF_THE_FOREST_API FInventoryItem : public FTableRowBase
{
	GENERATED_BODY()

public:
	FInventoryItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Value;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* Thumbnail;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    bool operator==(const FInventoryItem&amp; OtherItem) const
    {
        if (ItemID == OtherItem.ItemID)
            return true;
        return false;
    }
	
};
