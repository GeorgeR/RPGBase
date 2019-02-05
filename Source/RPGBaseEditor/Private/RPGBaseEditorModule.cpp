#include "RPGBaseEditorModule.h"

#include "SlateStyle.h"
#include "IPluginManager.h"
#include "SlateStyleRegistry.h"

#include "IconTextureThumbnailRenderer.h"

#include "AssetTypeActions_RPGItem.h"
#include "AssetTypeActions_RPGContainer.h"

DEFINE_LOG_CATEGORY(LogRPGBaseEditor);

#define LOCTEXT_NAMESPACE "FRPGBaseEditorModule"

void FRPGBaseEditorModule::StartupModule()
{
	RPGItemAssetTypeActions = MakeShareable(new FAssetTypeActions_RPGItem);
	RPGContainerAssetTypeActions = MakeShareable(new FAssetTypeActions_RPGContainer);

	IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>(TEXT("AssetTools")).Get();

	AssetTools.RegisterAssetTypeActions(RPGItemAssetTypeActions.ToSharedRef());
	AssetTools.RegisterAssetTypeActions(RPGContainerAssetTypeActions.ToSharedRef());

	//UThumbnailManager::Get().RegisterCustomRenderer(URPGItem::StaticClass(), UIconTextureThumbnailRenderer::StaticClass());

	StyleSet = MakeShareable(new FSlateStyleSet(TEXT("RPGBaseEditorStyle")));

	auto ContentPath = IPluginManager::Get().FindPlugin(TEXT("RPGBase"))->GetBaseDir();
	StyleSet->SetContentRoot(FPaths::Combine(ContentPath, TEXT("Content")));

	auto AssetIconPath = TEXT("Editor/Slate/Icons/AssetIcons/");

	auto RPGItemThumbnailBrush = new FSlateImageBrush(StyleSet->RootToContentDir(FPaths::Combine(AssetIconPath, TEXT("RPGItem_64x")), TEXT(".png")), FVector2D(64.0f, 64.0f));
	StyleSet->Set(TEXT("ClassThumbnail.RPGItem"), RPGItemThumbnailBrush);

	auto RPGContainerThumbnailBrush = new FSlateImageBrush(StyleSet->RootToContentDir(FPaths::Combine(AssetIconPath, TEXT("RPGContainer_64x")), TEXT(".png")), FVector2D(64.0f, 64.0f));
	StyleSet->Set(TEXT("ClassThumbnail.RPGContainer"), RPGContainerThumbnailBrush);

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
}

void FRPGBaseEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded(TEXT("AssetTools")))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>(TEXT("AssetTools")).Get();

		AssetTools.UnregisterAssetTypeActions(RPGItemAssetTypeActions.ToSharedRef());
		AssetTools.UnregisterAssetTypeActions(RPGContainerAssetTypeActions.ToSharedRef());
	}

	FSlateStyleRegistry::UnRegisterSlateStyle(StyleSet->GetStyleSetName());
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FRPGBaseEditorModule, RPGBaseEditor)
