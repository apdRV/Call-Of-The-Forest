// Fill out your copyright notice in the Description page of Project Settings.


#include "Login.h"

void ULogin::TryLogin()
{
		FString UserName = UserNameInput->GetText().ToString().TrimStartAndEnd();
		FString Password = PasswordInput->GetText().ToString();
        bool result = AMyDatabase::Login(UserName, Password);
        if (result) {
            login_success = true;
        }
		else {
            Clean();
        }
}

void ULogin::NativeOnInitialized()
{
	LoginAction->OnClicked.AddDynamic(this, &ULogin::TryLogin);
	Super::NativeOnInitialized();
}

void ULogin::Clean()
{
	UserNameInput->SetText(FText::GetEmpty());
	PasswordInput->SetText(FText::GetEmpty());
	UserNameInput->SetFocus();
}


