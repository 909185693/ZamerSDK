// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class ZamerSDK : ModuleRules
{
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }

    public ZamerSDK(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        //ue4 v20��ĸĶ�����������Ļ����뽫����û�н�"__cplusplus"����ΪԤ�������꣬��"0"�滻��#if/#elif�����Ĵ��󣡣���
        //http://api.unrealengine.com/CHN/Programming/UnrealBuildSystem/ModuleFiles/
        bEnableUndefinedIdentifierWarnings = false;

        PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
		});
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
		});
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "Json"
		});
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "HTTP"
		});

        PrivateIncludePathModuleNames.AddRange(new string[] { "HTTP" });		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
		});

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			string LibrariesPath = Path.Combine(ThirdPartyPath, "ZamerSDK", "Win64");
            PublicSystemLibraryPaths.Add(LibrariesPath);
            PublicDelayLoadDLLs.Add("ZMVR.dll");
			RuntimeDependencies.Add(Path.Combine(LibrariesPath, "ZMVR.dll"));
            //if (Target.Platform == UnrealTargetPlatform.Win32)
            //{
            //    string LibrariesPathWin32 = Path.Combine(ThirdPartyPath, "ZamerSDK", "Win32");
            //    PublicSystemLibraryPaths.Add(LibrariesPathWin32);
            //    PublicDelayLoadDLLs.Add("ZamerOpenAPI.dll");
            //    RuntimeDependencies.Add(Path.Combine(LibrariesPathWin32, "ZamerOpenAPI.dll"));
            //}

            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                string LibrariesPathWin64 = Path.Combine(ThirdPartyPath, "ZamerSDK", "Win64");
                PublicSystemLibraryPaths.Add(LibrariesPathWin64);
                PublicDelayLoadDLLs.Add("ZamerOpenAPI.dll");
                RuntimeDependencies.Add(Path.Combine(LibrariesPathWin64, "ZamerOpenAPI.dll"));
            }         
        }
	}
}
