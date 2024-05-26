// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryController.h"
#include "InventoryGameState.h"

AInventoryController::AInventoryController(){
}

bool AInventoryController::AddItemToInventoryByID(FName ID){
    AInventoryGameState* GameState = Cast<AInventoryGameState>(GetWorld()->GetGameState());
    UDataTable* ItemTable = GameState->GetItemDB();
    FInventoryItem* ItemToAdd = ItemTable->FindRow<FInventoryItem>(ID, "");

    if (ItemToAdd){
            Inventory.Add(*ItemToAdd);
            ReloadInventory();
            return true;
    }
    return false;
}

    void AInventoryController::Interact()
{
}

void AInventoryController::SetupInputComponent()
{
    Super::SetupInputComponent();
    InputComponent->BindAction("Interact", IE_Pressed, this, &AInventoryController::Interact);
}
