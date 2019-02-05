#pragma once

#include "EngineMinimal.h"
#include "Engine/Engine.h"
#include "ModuleManager.h"

RPGBASE_API DECLARE_LOG_CATEGORY_EXTERN(LogRPGBase, Log, All);

class FRPGBaseModule 
	: public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
