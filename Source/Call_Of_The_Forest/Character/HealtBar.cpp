// Fill out your copyright notice in the Description page of Project Settings.


#include "HealtBar.h"

void UHealtBar::NativeConstruct(){
    Super::NativeConstruct();

    Player = Cast<AMainPaperCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

float UHealtBar::CalculateHealthPercentage(){
    if (Player){
        return Player->GetHealth() / Player->GetMaxHealth();
    }
    return 0.0f;
}
