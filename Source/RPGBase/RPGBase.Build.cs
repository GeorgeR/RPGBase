using UnrealBuildTool;

public class RPGBase : ModuleRules
{
	public RPGBase(ReadOnlyTargetRules Target) 
        : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

	    PublicDefinitions.Add("WITH_NETWORKING=1");
		
		PublicIncludePaths.AddRange(
			new string[] {
				"RPGBase/Public"
			});

		PrivateIncludePaths.AddRange(
			new string[] {
				"RPGBase/Private"
			});

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core"
			});

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "UMG"
			});

		DynamicallyLoadedModuleNames.AddRange(new string[] { });
	}
}