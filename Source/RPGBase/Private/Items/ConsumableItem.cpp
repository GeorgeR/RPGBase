#include "ConsumableItem.h"

UConsumableItem::UConsumableItem()
{
	bIsStackable = true;
	MaxStackSize = 10;
}

bool UConsumableItem::CanUse_Implementation(AActor* TargetUser, FItemInstance& ItemInstance)
{
	return CanConsume(TargetUser, ItemInstance);
}

void UConsumableItem::Use_Implementation(AActor* TargetUser, FItemInstance& ItemInstance)
{
	if (CanConsume(TargetUser, ItemInstance))
		Consume(TargetUser, ItemInstance);
}

void UConsumableItem::PostUse_Implementation(FItemInstance& ItemInstance)
{
	ItemInstance.RemoveFromStack(1);
}


bool UConsumableItem::CanConsume_Implementation(AActor* TargetConsumer, FItemInstance& ItemInstance)
{
	// TODO: More checks like if the TargetConsumer owns the item

	return ItemInstance.StackSize > 0;
}

void UConsumableItem::Consume_Implementation(AActor* TargetConsumer, FItemInstance& ItemInstance)
{
	// TODO
}
