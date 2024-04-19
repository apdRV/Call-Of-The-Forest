// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryController.h"
#include "InventoryGameState.h"

AInventoryController::AInventoryController(){
    InventorySlotLimit = 20;
}

bool AInventoryController::AddItemToInventoryByID(FName ID){
    AInventoryGameState* GameState = Cast<AInventoryGameState>(GetWorld()->GetGameState());
    UDataTable* ItemTable = GameState->GetItemDB();
    FInventoryItem* ItemToAdd = ItemTable->FindRow<FInventoryItem>(ID, "");

    if (ItemToAdd){
        if (Inventory.Num() < InventorySlotLimit){
            Inventory.Add(*ItemToAdd);
            ReloadInventory();
            return true;
        }
    }
    return false;
}

    void AInventoryController::Interact()
{
    if (CurrentInteractable)
    {
        CurrentInteractable->Interact(this);
    }
}

void AInventoryController::SetupInputComponent()
{
    Super::SetupInputComponent();
    InputComponent->BindAction("Interact", IE_Pressed, this, &AInventoryController::Interact);
}
