#pragma once

#include "AssetTypeActions_Base.h"

#include "Items/RPGContainer.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"

class FAssetTypeActions_RPGContainer 
    : public FAssetTypeActions_Base
{
public:
	virtual FText GetName() const override
	{
		return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_RPGContainer", "Container");
	}

	virtual FColor GetTypeColor() const override
	{
		return FColor(255, 128, 64);
	}

	virtual UClass* GetSupportedClass() const override
	{
		return URPGContainer::StaticClass();
	}

	uint32 GetCategories() override
	{
		return EAssetTypeCategories::Gameplay;
	}
};
