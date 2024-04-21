// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDatabase.h"

// Sets default values
AMyDatabase::AMyDatabase()
{
}
void AMyDatabase::CreateAccount(FString name, FString password) {
  const FString DbPath = "../../../Content/Database/Users.db";
  const FString CreateSQL = TEXT("INSERT INTO Users (Username, PasswordHash) VALUES (@Username, @PasswordHash) RETURNING UserID;");
  const FString Username = TEXT("@Username");
  const FString PasswordHash = TEXT("@PasswordHash");
  FSQLiteDatabase* AutorisationDb = new FSQLiteDatabase(); 
  AutorisationDb -> Open(*DbPath, OpenMode);
  FSQLitePreparedStatement* Statement = new FSQLitePreparedStatement(); 
  Statement->Create(*AutorisationDb, *CreateSQL, ESQLitePreparedStatementFlags::Persistent); 
  Statement->SetBindingValueByName(*Username, name);
  Statement->SetBindingValueByName(*PasswordHash, 15);
  Statement->Execute();
  Statement->Destroy();
  delete Statement;
  AutorisationDb->Close();  
  delete AutorisationDb;
}