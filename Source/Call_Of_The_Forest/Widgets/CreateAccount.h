// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Blueprint/UserWidget.h"
#include "../Database/MyDatabase.h"
#include "CreateAccount.generated.h"

/**
 * 
 */
UCLASS()
class CALL_OF_THE_FOREST_API UCreateAccount : public UUserWidget
{
	public:
	GENERATED_BODY()
	virtual void NativeOnInitialized() final;

	UFUNCTION()
	virtual void CreateUserAccount();

	void Clean();
	
	UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls", meta = (BindWidget))
	UEditableTextBox* UserNameInput = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls", meta = (BindWidget))
	UEditableTextBox* PasswordInput = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls", meta = (BindWidget))
	UButton* CreateAccountAction = nullptr;

};
