// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RadioSilence : ModuleRules
{
	public RadioSilence(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
