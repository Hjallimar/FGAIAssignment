// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AITeam12 : ModuleRules
{
	public AITeam12(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

		PublicIncludePaths.Add("AITeam12");
	}
}
