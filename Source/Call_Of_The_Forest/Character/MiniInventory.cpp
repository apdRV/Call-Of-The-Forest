;// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniInventory.h"

void UMiniInventory::NativeConstruct(){
    Super::NativeConstruct();

    Player = Cast<AMainPaperCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

int UMiniInventory::CalculateTrophyQuantity(){
    if (Player){
        return Player->TrophyQuantity;
    }
    return 0;
}

int UMiniInventory::CalculateMeatQuantity(){
    if (Player){
        return Player->MeatQuantity;
    }
    return 0;
}

int UMiniInventory::CalculateWoodQuantity(){
    if (Player){
        return Player->WoodQuantity;
    }
    return 0;
}

int UMiniInventory::CalculateStoneQuantity(){
    if (Player){
        return Player->StoneQuantity;
    }
    return 0;
}