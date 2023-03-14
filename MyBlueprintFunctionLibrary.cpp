// Copyright Marcelo Coelho


#include "MyBlueprintFunctionLibrary.h"

#include "JsonObjectConverter.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonSerializer.h"


FString UMyBlueprintFunctionLibrary::ReadStringFromFile(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage)
{
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Failed to read file. File does not exist"));
		return "";
	}
	FString RetString = "";
	if (!FFileHelper::LoadFileToString(RetString, *FilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Failed to read file. Unable to read file %s"), *FilePath);
		return "";
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("File read successfully"));
	return RetString;
}

FAqTestStruct UMyBlueprintFunctionLibrary::ReadStructFromJsonFile(FString JsonFilePath, bool& bOutSuccess,
	FString& OutInfoMessage)
{
	TSharedPtr<FJsonObject> JsonObject = ReadJson(JsonFilePath, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("No bOutSuccess: %s"), *JsonFilePath);
		return FAqTestStruct();
	}

	FAqTestStruct RetAqTestStruct;
	if (!FJsonObjectConverter::JsonObjectToUStruct<FAqTestStruct>(JsonObject.ToSharedRef(), &RetAqTestStruct))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Unable to convert Json file %s"), *JsonFilePath);

		UE_LOG(LogTemp, Warning, TEXT("Unable to convert Json file: %s"), *OutInfoMessage);
		
		return FAqTestStruct();
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Json file read successfully %s"), *JsonFilePath);

	UE_LOG(LogTemp, Warning, TEXT("Json from inside function: %s"), *RetAqTestStruct.MyString);
	
	return RetAqTestStruct;
}

TSharedPtr<FJsonObject> UMyBlueprintFunctionLibrary::ReadJson(FString JsonFilePath, bool& bOutSuccess,
                                                              FString& OutInfoMessage)
{

	FString JsonString = ReadStringFromFile(JsonFilePath, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{
		return nullptr;
	}

	TSharedPtr<FJsonObject> RetJsonObject;
	if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), RetJsonObject))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Failed to read file. Unable to read file %s"), *JsonString);
		return nullptr;
	}
	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Read Json Succeeded %s"), *JsonFilePath);
	return RetJsonObject;
}
