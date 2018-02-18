#include "ContainerComponent.h"

UContainerComponent::UContainerComponent()
{
	Items.Init(UNullItem::Get(), GetCapacity());
}

/* By default, this won't add the item if the slot is occupied. You might customize it to swap items with the source. */
bool UContainerComponent::AddItem_Implementation(UItem * InItem, int32 InSlot)
{
	if (InSlot == -1)
		InSlot = GetFirstAvailableSlot();

	if (IsSlotOccupied(InSlot))
		return false;

	Items[InSlot] = InItem;
	return true;
}

UItem* UContainerComponent::RemoveItem_Implementation(int32 InSlot)
{
	if (!IsSlotOccupied(InSlot))
		return nullptr;

	UItem* Item = Items[InSlot];
	Items.RemoveAt(InSlot, 1, false);
	Items[InSlot] = UNullItem::Get();

	return Item;
}

void UContainerComponent::SwapItems_Implementation(int32 InSlotLeft, int32 InSlotRight)
{
	if (!IsSlotOccupied(InSlotLeft))
		return;

	Items.Swap(InSlotLeft, InSlotRight);
}

int32 UContainerComponent::GetFirstAvailableSlot()
{
	for (auto i = 0; i < Items.Num(); i++)
	{
		if (Items[i] == nullptr || Items[i]->GetClass() == UNullItem::StaticClass())
			return i;
	}

	return -1;
}