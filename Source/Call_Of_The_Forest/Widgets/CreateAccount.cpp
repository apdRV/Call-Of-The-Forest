// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateAccount.h"

void UCreateAccount::CreateUserAccount()
{
		FString UserName = UserNameInput->GetText().ToString().TrimStartAndEnd();
		FString Password = PasswordInput->GetText().ToString();
        AMyDatabase::CreateAccount(UserName, Password);
		Clean();
}

void UCreateAccount::NativeOnInitialized()
{
	CreateAccountAction->OnClicked.AddDynamic(this, &UCreateAccount::CreateUserAccount);
	Super::NativeOnInitialized();
}

void UCreateAccount::Clean()
{
	UserNameInput->SetText(FText::GetEmpty());
	PasswordInput->SetText(FText::GetEmpty());
	UserNameInput->SetFocus();
}


