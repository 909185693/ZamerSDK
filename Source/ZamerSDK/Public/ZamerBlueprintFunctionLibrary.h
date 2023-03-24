// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ZamerBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ZAMERSDK_API UZamerBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "ZamerSDK")
	static void ZamerCheckDll(const FString& DeveloperID, const FString& GameID, const FString& Token, const FString& Checkcode);

	UFUNCTION(BlueprintCallable, Category = "ZamerSDK")
	static FString GetDeviceSN();

	UFUNCTION(BlueprintCallable, Category = "ZamerSDK")
	static int32 GetUserId();

	UFUNCTION(BlueprintCallable, Category = "ZamerSDK")
	static int32 GetMerchantId();

	UFUNCTION(BlueprintCallable, Category = "ZamerSDK")
	static FString GetUserNickName();

	UFUNCTION(BlueprintCallable, Category = "ZamerSDK")
	static void ZMUploadScore(int Score);
};
