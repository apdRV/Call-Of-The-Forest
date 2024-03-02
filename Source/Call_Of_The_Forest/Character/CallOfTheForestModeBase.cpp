// Fill out your copyright notice in the Description page of Project Settings.


#include "CallOfTheForestModeBase.h"


ACallOfTheForestModeBase::ACallOfTheForestModeBase() : Super()
{
    ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MainPaperCharacter"));
    DefaultPawnClass = PlayerPawnBPClass.Class;
}