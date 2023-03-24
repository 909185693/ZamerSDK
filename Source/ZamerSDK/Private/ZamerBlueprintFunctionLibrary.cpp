// Fill out your copyright notice in the Description page of Project Settings.

#include "ZamerBlueprintFunctionLibrary.h"
#include "ZamerSDKHelper.h"
#include <Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include <Runtime/Core/Public/Misc/Paths.h>

ZamerSDKHelper *zmsdk = new ZamerSDKHelper();

//调用实现函数
//Implementation function for calling procedure.
void UZamerBlueprintFunctionLibrary::ZamerCheckDll(const FString& DeveloperID, const FString& GameID, const FString& Token, const FString& Checkcode)
{
	zmsdk->ZMVRCheckDll(Token, Checkcode, DeveloperID, GameID);
}

FString UZamerBlueprintFunctionLibrary::GetDeviceSN()
{
	return  zmsdk->GetDeviceSN();
}

int32 UZamerBlueprintFunctionLibrary::GetUserId()
{
	return  zmsdk->GetUserId();
}

int32 UZamerBlueprintFunctionLibrary::GetMerchantId()
{
	return  zmsdk->GetMerchantId();
}

FString UZamerBlueprintFunctionLibrary::GetUserNickName()
{
	return zmsdk->GetNickname();
}

void UZamerBlueprintFunctionLibrary::ZMUploadScore(int Score)
{
	zmsdk->UpDataZM(Score);
}