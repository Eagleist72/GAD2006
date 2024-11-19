// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LabWork_1 : ModuleRules
{
	public LabWork_1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
