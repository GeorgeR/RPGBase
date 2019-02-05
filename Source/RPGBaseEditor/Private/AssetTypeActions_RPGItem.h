#pragma once

#include "AssetTypeActions_Base.h"

#include "Items/RPGItem.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

class FAssetTypeActions_RPGItem 
    : public FAssetTypeActions_Base
{
public:
	FText GetName() const override
	{
		return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_RPGItem", "Item");
	}

	FColor GetTypeColor() const override
	{
		return FColor(255, 128, 64);
	}

	UClass* GetSupportedClass() const override
	{
		return URPGItem::StaticClass();
	}

	uint32 GetCategories() override
	{
		return EAssetTypeCategories::Gameplay;
	}

	virtual class UThumbnailInfo* GetThumbnailInfo(UObject* Asset) const override;
};
