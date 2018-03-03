#include "ContainerInstanceComponent.h"
#include "UnrealNetwork.h"

UContainerInstanceComponent::UContainerInstanceComponent()
{
	TArray<FItemInstance>& Items = this->Items;
	Items.Init(UNullItem::GetInstance(), GetCapacity());
}

/* By default, this won't add the item if the slot is occupied. You might customize it to swap items with the source. */
bool UContainerInstanceComponent::AddItem_Implementation(const FItemInstance& InItem, int32 InSlot)
{
#if WITH_NETWORKING
	if (GetOwner()->HasAuthority())
	{
#endif
		if (InSlot == -1)
			InSlot = GetFirstAvailableSlot();

		if (IsSlotOccupied(InSlot))
			return false;

		TArray<FItemInstance>& Items = this->Items;
		Items[InSlot] = InItem;
		return true;

#if WITH_NETWORKING
	}

	Server_AddItem(InItem, InSlot);
	return false;
#endif
}

FItemInstance UContainerInstanceComponent::RemoveItem_Implementation(int32 InSlot)
{
#if WITH_NETWORKING
	if (GetOwner()->HasAuthority())
	{
#endif
		if (!IsSlotOccupied(InSlot))
			return UNullItem::GetInstance();

		TArray<FItemInstance>& Items = this->Items;
		FItemInstance& Item = Items[InSlot];
		Items.RemoveAt(InSlot, 1, false);
		Items[InSlot] = UNullItem::GetInstance();

		return Item;
#if WITH_NETWORKING
	}

	Server_RemoveItem(InSlot);
	return UNullItem::GetInstance();
#endif
}

void UContainerInstanceComponent::SwapItems_Implementation(int32 InSlotLeft, int32 InSlotRight)
{
#if WITH_NETWORKING
	if (GetOwner()->HasAuthority())
	{
#endif
		if (!IsSlotOccupied(InSlotLeft))
			return;

		TArray<FItemInstance>& Items = this->Items;
		Items.Swap(InSlotLeft, InSlotRight);
#if WITH_NETWORKING
	}

	Server_SwapItems(InSlotLeft, InSlotRight);
#endif
}

void UContainerInstanceComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UContainerInstanceComponent, Items);
}

// All these do is essentially ensure the wrapped calls are run on the server
bool UContainerInstanceComponent::Server_AddItem_Validate(const FItemInstance& InItem, int32 InSlot /*= -1*/) { return true; }

void UContainerInstanceComponent::Server_AddItem_Implementation(const FItemInstance& InItem, int32 InSlot /*= -1*/) { AddItem(InItem, InSlot); }

bool UContainerInstanceComponent::Server_RemoveItem_Validate(int32 InSlot) { return true; }

void UContainerInstanceComponent::Server_RemoveItem_Implementation(int32 InSlot) { RemoveItem(InSlot); }

bool UContainerInstanceComponent::Server_SwapItems_Validate(int32 InSlotLeft, int32 InSlotRight) { return true; }

void UContainerInstanceComponent::Server_SwapItems_Implementation(int32 InSlotLeft, int32 InSlotRight) { SwapItems(InSlotLeft, InSlotRight); }

int32 UContainerInstanceComponent::GetFirstAvailableSlot()
{
	TArray<FItemInstance>& Items = this->Items;
	for (auto i = 0; i < Items.Num(); i++)
	{
		if (Items[i].IsNullItem())
			return i;
	}

	return -1;
}

bool UContainerInstanceComponent::IsSlotOccupied(int32 InSlot)
{
	TArray<FItemInstance>& Items = this->Items;
	return IsSlotInRange(InSlot) && !Items[InSlot].IsNullItem();
}