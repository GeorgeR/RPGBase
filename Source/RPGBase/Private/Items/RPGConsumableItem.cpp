#include "Items/RPGConsumableItem.h"

URPGConsumableItem::URPGConsumableItem()
{
	bIsStackable = true;
	MaxStackSize = 10;
}

bool URPGConsumableItem::CanUse_Implementation(const TScriptInterface<IRPGUserInterface>& TargetUser, FRPGItemInstance& ItemInstance)
{
	return CanConsume(TargetUser, ItemInstance);
}

void URPGConsumableItem::Use_Implementation(const TScriptInterface<IRPGUserInterface>& TargetUser, FRPGItemInstance& ItemInstance)
{
	if (CanConsume(TargetUser, ItemInstance))
		Consume(TargetUser, ItemInstance);
}

void URPGConsumableItem::PostUse_Implementation(FRPGItemInstance& ItemInstance)
{
	ItemInstance.RemoveFromStack(1);
}


bool URPGConsumableItem::CanConsume_Implementation(const TScriptInterface<IRPGUserInterface>& TargetConsumer, FRPGItemInstance& ItemInstance)
{
	// TODO: More checks like if the TargetConsumer owns the item

	return ItemInstance.StackSize > 0;
}

void URPGConsumableItem::Consume_Implementation(const TScriptInterface<IRPGUserInterface>& TargetConsumer, FRPGItemInstance& ItemInstance)
{
	// TODO
}
