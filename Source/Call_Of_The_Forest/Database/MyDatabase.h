// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <string>
#include "SQLiteDatabase.h"
#include "../Character/MainPaperCharacter.h"
#include "Misc/Paths.h"
#include "Misc/SecureHash.h"
#include "MyDatabase.generated.h"

UCLASS()
class CALL_OF_THE_FOREST_API AMyDatabase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyDatabase();
	static void CreateAccount(FString name, FString password);
};
