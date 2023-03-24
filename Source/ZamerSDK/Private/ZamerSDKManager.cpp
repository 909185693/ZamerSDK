// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ZamerSDKManager.h"
#include "ZamerSDKHelper.h"

UZamerSDKManager* UZamerSDKManager::Instance = nullptr;

UZamerSDKManager::UZamerSDKManager(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UZamerSDKManager& UZamerSDKManager::Get()
{
	if (Instance == nullptr)
	{
		Instance = NewObject<UZamerSDKManager>();
	}

	return *Instance;
}

void UZamerSDKManager::Init()
{
		// ZMVR计费SDK授权,平台方要求验证不通过直接提示退出游戏
	bool bEnabled = true;
#if UE_EDITOR
	if (!GConfig->GetBool(TEXT("ZamerSDK"), TEXT("bEnabled"), bEnabled, GEngineIni))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to obtain bEnabled from [ZamerSDK] engine config."));
	}
#endif
	if (bEnabled)
	{
		FString Token;
		if (!GConfig->GetString(TEXT("ZamerSDK"), TEXT("Token"), Token, GEngineIni))
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to obtain Token from [ZamerSDK] engine config."));
		}

		FString CheckCode;
		if (!GConfig->GetString(TEXT("ZamerSDK"), TEXT("CheckCode"), CheckCode, GEngineIni))
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to obtain CheckCode from [ZamerSDK] config."));
		}

		FString DevelopID;
		if (!GConfig->GetString(TEXT("ZamerSDK"), TEXT("DevelopID"), DevelopID, GEngineIni))
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to obtain DevelopID from [ZamerSDK] config."));
		}

		FString ContentID;
		if (!GConfig->GetString(TEXT("ZamerSDK"), TEXT("ContentID"), ContentID, GEngineIni))
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to obtain ContentID from [ZamerSDK] config."));
		}

		//ZMVR验证接口,通过接口验证才能开始游戏，否则退出游戏(必调接口)
		ZamerSDKHelper* ZMSDK = new ZamerSDKHelper();
		if (ZMSDK->ZMVRCheckDll(Token, CheckCode, DevelopID, ContentID) == 0)
		{
			UE_LOG(LogTemp, Log, TEXT("FZmerAuthorization::Init ZMVRCheckDll."));
			UE_LOG(LogTemp, Log, TEXT("设备码：%s"), *ZMSDK->GetDeviceSN());
			UE_LOG(LogTemp, Log, TEXT("用户ID：%d"), ZMSDK->GetUserId());
			UE_LOG(LogTemp, Log, TEXT("商家ID：%d"), ZMSDK->GetMerchantId());
			ZMSDK->InitAPI();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("FZmerAuthorization::Init.ZMVRCheckDll fail"));

			//退出游戏
			FGenericPlatformMisc::RequestExit(false);
		}
	}
}

void UZamerSDKManager::Shutdown()
{
	if (Instance != nullptr)
	{
		Instance = nullptr;
	}
}

bool UZamerSDKManager::IsValid()
{
	return true;
}