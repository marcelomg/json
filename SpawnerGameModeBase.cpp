// Copyright Epic Games, Inc. All Rights Reserved.


#include "SpawnerGameModeBase.h"

#include "MyBlueprintFunctionLibrary.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

ASpawnerGameModeBase::ASpawnerGameModeBase()
{
	
}

void ASpawnerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	FString JsonFilePath = TEXT("D:\\Temp\\MyJson.json");
	bool bOutSuccess = false;
	FString OutInfoMessage = TEXT("Json Successfull");
	FAqTestStruct MyStruct = JsonApi->ReadStructFromJsonFile(JsonFilePath, bOutSuccess, OutInfoMessage);

	UE_LOG(LogTemp, Warning, TEXT("MyStruct String: %s"), *MyStruct.MyString);
	UE_LOG(LogTemp, Warning, TEXT("MyStruct Float %f"), MyStruct.MyFloat);

	for (int32 i = 0; i < MyStruct.Enemies.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy : %d"), MyStruct.Enemies[i]);
	}
}

void ASpawnerGameModeBase::SpawnEnemy()
{

	UE_LOG(LogTemp, Warning, TEXT("Counter is %d"), Counter);
	
}
