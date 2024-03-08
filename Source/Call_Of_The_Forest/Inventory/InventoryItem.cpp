// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem.h"

FInventoryItem::FInventoryItem()
{
    this->Name = FText::FromString("No Name");
    this->Value = 1;
    this->Description = FText::FromString("No Description");
}