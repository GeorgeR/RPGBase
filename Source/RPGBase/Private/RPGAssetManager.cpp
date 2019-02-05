#include "RPGAssetManager.h"
#include "Engine/Engine.h"
#include "LogMacros.h"

#include "RPGBaseModule.h"
#include "RPGItem.h"

const FPrimaryAssetType URPGAssetManager::ConsumableItemType = TEXT("Consumable");
const FPrimaryAssetType URPGAssetManager::EquippableItemType = TEXT("Equippable");
const FPrimaryAssetType URPGAssetManager::ResourceItemType = TEXT("Resource");
const FPrimaryAssetType URPGAssetManager::WeaponItemType = TEXT("Weapon");

URPGAssetManager& URPGAssetManager::Get()
{
	auto Self = Cast<URPGAssetManager>(GEngine->AssetManager);
	if (Self)
		return *Self;
	else
	{
		UE_LOG(LogRPGBase, Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini, must be RPGAssetManager!"));
		return *NewObject<URPGAssetManager>();
	}
}

URPGItem* URPGAssetManager::ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning /*= true*/)
{
	auto ItemPath = GetPrimaryAssetPath(PrimaryAssetId);
	auto Item = Cast<URPGItem>(ItemPath.TryLoad());
	if (bLogWarning && Item == nullptr)
		UE_LOG(LogRPGBase, Warning, TEXT("Failed to load item for id %s!"), *PrimaryAssetId.ToString());

	return Item;
}
