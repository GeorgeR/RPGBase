#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"

#include "RPGAssetManager.generated.h"

class URPGItem;

UCLASS()
class RPGBASE_API URPGAssetManager
	: public UAssetManager
{
	GENERATED_BODY()

public:
	URPGAssetManager() { }

	static const FPrimaryAssetType ConsumableItemType;
	static const FPrimaryAssetType EquippableItemType;
	static const FPrimaryAssetType ResourceItemType;
	static const FPrimaryAssetType WeaponItemType;

	/** Returns the current AssetManager object */
	static URPGAssetManager& Get();

	/**
	 * Synchronously loads an RPGItem subclass, this can hitch but is useful when you cannot wait for an async load
	 * This does not maintain a reference to the item so it will garbage collect if not loaded some other way
	 *
	 * @param PrimaryAssetId The asset identifier to load
	 * @param bDisplayWarning If true, this will log a warning if the item failed to load
	 */
	URPGItem* ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning = true);
};
