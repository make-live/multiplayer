// Built with ❤ by Make Live

using UnrealBuildTool;

public class MakeLiveMultiplayer : ModuleRules
{
	public MakeLiveMultiplayer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {});
		PublicDependencyModuleNames.Add("Core");
		PublicDependencyModuleNames.Add("CoreUObject");
		PublicDependencyModuleNames.Add("Engine");
		PublicDependencyModuleNames.Add("InputCore");
		PublicDependencyModuleNames.Add("GameplayAbilities");
		PublicDependencyModuleNames.Add("OnlineSubsystem");
        	PublicDependencyModuleNames.Add("HeadMountedDisplay");
        	PublicDependencyModuleNames.Add("GameplayAbilities");
        	PublicDependencyModuleNames.Add("GameplayTags");
        	PublicDependencyModuleNames.Add("GameplayTasks");

		PrivateDependencyModuleNames.AddRange(new string[] {});
	}
}
