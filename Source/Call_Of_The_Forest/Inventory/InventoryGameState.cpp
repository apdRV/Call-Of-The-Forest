// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGameState.h"

AInventoryGameState::AInventoryGameState()
{
    static ConstructorHelpers::FObjectFinder<UDataTable> BP_ItemDB(TEXT("DataTable'/Game/Data/ItemDB.ItemDB'"));
    if (BP_ItemDB.Succeeded())
    {
        ItemDB = BP_ItemDB.Object;
    }   
}

UDataTable* AInventoryGameState::GetItemDB() const 
{
    return ItemDB; 
}