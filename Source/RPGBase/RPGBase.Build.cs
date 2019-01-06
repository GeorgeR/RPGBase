using UnrealBuildTool;

public class RPGBase : ModuleRules
{
	public RPGBase(ReadOnlyTargetRules Target) 
        : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        /* Use networking */
	    PublicDefinitions.Add("WITH_NETWORKING=1");

        /* Use SpatialOS */
        PublicDefinitions.Add("WITH_SPATIALOS=1");

        /* Use Gameplay Abilities */
        PublicDefinitions.Add("WITH_ABILITIES=1");

	    if (Target.Version.MinorVersion <= 19)
	    {
            PublicIncludePaths.AddRange(
			    new string[] {
				    "RPGBase/Public"
			    });

		    PrivateIncludePaths.AddRange(
			    new string[] {
				    "RPGBase/Private"
			    });
        }

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

        if (PublicDefinitions.Contains("WITH_NETWORKING=1"))
        {

        }

        if (PublicDefinitions.Contains("WITH_NETWORKING=1")
            && PublicDefinitions.Contains("WITH_SPATIALOS=1"))
        {

        }

        if (PublicDefinitions.Contains("WITH_ABILITIES=1"))
        {
            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "GameplayAbilities",
                    "GameplayTags",
                    "GameplayTasks"
                });
        }
    }
}
