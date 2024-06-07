// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathScreen.h"
#include "Kismet/GameplayStatics.h"

void UDeathScreen::NativeConstruct(){
    Super::NativeConstruct();

    //Player = Cast<AMainPaperCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    //World = AStaticWorld::GetStaticWorld();
//     if(World != nullptr)
//     {
//         AMainPaperCharacter* Temp = dynamic_cast<AMainPaperCharacter*>(World->GetActor("MainCharacter")[0]);
//         if(Temp){
//             Player = Temp;
//         }
//     }
}

// void UDeathScreen::BeginPlay()
// {
//     if(World != nullptr)
//     {
//         AMainPaperCharacter* Temp = dynamic_cast<AMainPaperCharacter*>(World->GetActor("MainCharacter")[0]);
//         if(Temp){
//             Player = Temp;
//         }
//     }
// }