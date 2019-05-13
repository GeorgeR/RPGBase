#include "Items/RPGItem.h"

const FText& URPGItem::GetDisplayName(const FRPGItemInstance& ItemInstance) const
{
	check(ItemInstance.ItemClass == this->GetClass());

	if (!this->bIsStackable)
		return DisplayNameSingular;

	return ItemInstance.StackSize > 1 ? DisplayNamePlural : DisplayNameSingular;
}

FPrimaryAssetId URPGItem::GetPrimaryAssetId() const
{
	/* TODO: For blueprints, we need to strip then _C suffix */
	return FPrimaryAssetId(AssetType, GetFName());
}
