// Fill out your copyright notice in the Description page of Project Settings.
#include "CallOfTheForestModeBase.h"
ACallOfTheForestModeBase::ACallOfTheForestModeBase() : Super()
{
    ConstructorHelpers::FClassFinder<APawn> MainPaperCharacterClass(TEXT("/Script/CoreUObject.Class'/Script/Call_Of_The_Forest.MainPaperCharacter'"));
    if(MainPaperCharacterClass.Succeeded()){
        DefaultPawnClass = MainPaperCharacterClass.Class;
    }
    // ConstructorHelpers::FClassFinder<APawn> MobClass(TEXT("/Script/CoreUObject.Class'/Script/Call_Of_The_Forest.Mob'"));
    // if(MobClass.Succeeded()){
    //     SkeletonClass = MobClass.Class;
    // }

}