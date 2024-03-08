// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryController.h"

AInventoryController::AInventoryController(){
    InventorySlotLimit = 20;
}

AInventoryController::AddItemToInventoryByID(FName ID){
    AInventoryGameState* GameState = Cast(GetWorld()->GetGameState());
    UDataTable* ItemTable = GameState->GetItemDB();
    FInventoryItem* ItemToAdd = ItemTable->FindRow(ID, "");

    if (ItemToAdd){
        if (Inventory.Num() < InventorySlotLimit) BindAction("Interact", IE_Pressed, this, &amp;AInventoryController::Interact);
    }

    void AInventoryController::Interact()
{
    if (CurrentInteractable)
    {
        CurrentInteractable->Interact(this);
    }
}
}