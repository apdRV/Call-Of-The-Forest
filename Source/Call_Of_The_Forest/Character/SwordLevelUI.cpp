// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordLevelUI.h"

void USwordLevelUI::NativeConstruct(){
    Super::NativeConstruct();

    Player = Cast<AMainPaperCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

int USwordLevelUI::CalculateSwordLevel(){
    if (Player){
        return Player->SwordLevel;
    }
    return 0;
}

