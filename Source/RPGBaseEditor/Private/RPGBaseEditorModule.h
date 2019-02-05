#pragma once

#include "EngineMinimal.h"
#include "Engine/Engine.h"

#include "IRPGBaseEditorModule.h"

class FSlateStyleSet;

class FAssetTypeActions_RPGItem;
class FAssetTypeActions_RPGContainer;

RPGBASEEDITOR_API DECLARE_LOG_CATEGORY_EXTERN(LogRPGBaseEditor, Log, All);

class FRPGBaseEditorModule 
	: public IRPGBaseEditorModule
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedPtr<FSlateStyleSet> StyleSet;

	TSharedPtr<FAssetTypeActions_RPGItem> RPGItemAssetTypeActions;
	TSharedPtr<FAssetTypeActions_RPGContainer> RPGContainerAssetTypeActions;
};
