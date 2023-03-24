// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ZamerSDKManager.generated.h"

UCLASS(Config=Game)
class ZAMERSDK_API UZamerSDKManager : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	static UZamerSDKManager& Get();

	void Init();
	void Shutdown();
	bool IsValid();

private:
	static UZamerSDKManager* Instance;
};
