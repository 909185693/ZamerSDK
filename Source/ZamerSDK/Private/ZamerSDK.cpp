// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ZamerSDK.h"
#include "ZamerSDKManager.h"

#define LOCTEXT_NAMESPACE "FZamerSDKModule"

void FZamerSDKModule::StartupModule()
{
	UZamerSDKManager::Get().Init();
}

void FZamerSDKModule::ShutdownModule()
{
	UZamerSDKManager::Get().Shutdown();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FZamerSDKModule, ZamerSDK)