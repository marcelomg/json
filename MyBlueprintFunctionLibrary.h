// Copyright Marcelo Coelho

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

class FJsonObject;

USTRUCT(BlueprintType)
struct FAqTestStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool MyBool = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MyInt = 123;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat = 123.45f;

	UPROPERTY()
	FVector MyVector = {1.f, 2.f, 3.f};

	UPROPERTY()
	FRotator MyRotator = {1.f, 2.f, 3.f};

	UPROPERTY()
	TArray<int32> Enemies;

	UPROPERTY()
	FTransform MyTransform;

	FString MyOtherString = "This is not available in Json";
	
};

/**
 * 
 */
UCLASS()
class SPAWNER_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static FString ReadStringFromFile(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage);

	UFUNCTION(BlueprintCallable)
	static FAqTestStruct ReadStructFromJsonFile(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage);

	/**
	 * @param JsonFilePath
	 * @param bOutSuccess
	 * @param OutInfoMessage 
	 */
	static TSharedPtr<FJsonObject> ReadJson(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage);
	
};
