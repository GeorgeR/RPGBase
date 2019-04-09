using UnrealBuildTool;

public class RPGBaseEditor : ModuleRules
{
	public RPGBaseEditor(ReadOnlyTargetRules Target) 
        : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

	    if (Target.Version.MinorVersion <= 19)
	    {
            PublicIncludePaths.AddRange(
			    new string[] {
				    "RPGBaseEditor/Public"
			    });

		    PrivateIncludePaths.AddRange(
			    new string[] {
				    "RPGBaseEditor/Private"
			    });
        }

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
                "AssetTools",
                "BlueprintGraph",
                "ContentBrowser",
                "Core",
                "CoreUObject",
                "DesktopPlatform",
                "EditorStyle",
                "EditorWidgets",
                "Engine",
                "InputCore",
                "KismetCompiler",
                "LevelEditor",
                "MainFrame",
                "PropertyEditor",
                "RenderCore",
                "RHI",
                "TextureEditor",
                "UnrealEd",

                "RPGBase",
			});
        
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "AppFramework",
                "Projects",
                "Slate",
                "SlateCore",
                "WorkspaceMenuStructure",
			});

        if (Target.Version.MinorVersion <= 21)
        {
            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    "ShaderCore",
                });
        }
    }
}
