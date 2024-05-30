// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDatabase.h"

// Sets default values
FString AMyDatabase::username = "";

AMyDatabase::AMyDatabase()
{
}
void AMyDatabase::CreateAccount(FString name, FString password) {
  const FString DbPath = FPaths::ProjectContentDir() + "Database/Users.db";
  const FString CreateSQL = TEXT("INSERT INTO Users (Username, PasswordHash) VALUES (@Username, @PasswordHash);");
  const FString Username = TEXT("@Username");
  const FString PasswordHash = TEXT("@PasswordHash");
  FSQLiteDatabase* AutorisationDb = new FSQLiteDatabase(); 
  AutorisationDb -> Open(*DbPath, ESQLiteDatabaseOpenMode::ReadWrite);
  FSQLitePreparedStatement* Statement = new FSQLitePreparedStatement(); 
  Statement->Create(*AutorisationDb, *CreateSQL, ESQLitePreparedStatementFlags::Persistent);
  Statement->SetBindingValueByName(*Username, name);
  password = FMD5::HashAnsiString(*password);
  Statement->SetBindingValueByName(*PasswordHash, password);
  Statement->Execute();
  Statement->Destroy();
  delete Statement;
  AutorisationDb->Close();  
  delete AutorisationDb;
}

bool AMyDatabase::Login(FString name, FString password) {
  const FString DbPath = FPaths::ProjectContentDir() + "Database/Users.db";
  const FString CreateSQL = TEXT("SELECT * FROM Users WHERE Username = @Username AND PasswordHash = @PasswordHash;");
  const FString Username = TEXT("@Username");
  const FString PasswordHash = TEXT("@PasswordHash");
  FSQLiteDatabase* AutorisationDb = new FSQLiteDatabase(); 
  AutorisationDb -> Open(*DbPath, ESQLiteDatabaseOpenMode::ReadOnly);
  FSQLitePreparedStatement* Statement = new FSQLitePreparedStatement(); 
  Statement->Create(*AutorisationDb, *CreateSQL, ESQLitePreparedStatementFlags::Persistent);
  Statement->SetBindingValueByName(*Username, name);
  password = FMD5::HashAnsiString(*password);
  Statement->SetBindingValueByName(*PasswordHash, password);
  Statement->Execute();
  bool result = false;
  if (Statement->Step() == ESQLitePreparedStatementStepResult::Row){
    result = true;
  }
  Statement->Destroy();
  delete Statement;
  AutorisationDb->Close();  
  delete AutorisationDb;
  if (result) username = name;
  return result;
}

FString AMyDatabase::GetName() {
  return username;
}