// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RadioSilenceGame : ModuleRules
{
	public RadioSilenceGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Water", "UMG"}) ;
	}
}
