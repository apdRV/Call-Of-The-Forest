// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceBase.h"
#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"

void AResourceBase::Interact_Implementation(APlayerController* Controller)
{
    return;
}

FString AResourceBase::GetInteractText() const 
{
    return FString::Printf(TEXT("%s: Press F to %s"), *Name, *Action); 
}


