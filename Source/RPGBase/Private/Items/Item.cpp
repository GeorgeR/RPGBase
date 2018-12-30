#include "Item.h"

const FText& UItem::GetDisplayName(const FItemInstance& ItemInstance) const
{
	check(ItemInstance.ItemClass == this->GetClass());

	if (!this->bIsStackable)
		return DisplayNameSingular;

	return ItemInstance.StackSize > 1 ? DisplayNamePlural : DisplayNameSingular;
}

FPrimaryAssetId UItem::GetPrimaryAssetId() const
{
	/* TODO: For blueprints, we need to strip then _C suffix */
	return FPrimaryAssetId(AssetType, GetFName());
}
