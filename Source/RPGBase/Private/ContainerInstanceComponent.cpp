#include "ContainerInstanceComponent.h"
#include "UnrealNetwork.h"
#include "GameFramework/Actor.h"

UContainerInstanceComponent::UContainerInstanceComponent()
{
	if (Container != nullptr)
	{
		TArray<FItemInstance>& Items = this->Items;
		Items.Init(UNullItem::GetInstance(), GetCapacity());
	}

	this->Items.RegisterWithOwner(this);
}

/* By default, this won't add the item if the slot is occupied. You might customize it to swap items with the source. */
bool UContainerInstanceComponent::AddItem_Implementation(const FItemInstance& InItem, int32 InSlot)
{
	if (InSlot == -1)
		InSlot = GetFirstAvailableSlot();

	if (IsSlotOccupied(InSlot))
		return false;

	TArray<FItemInstance>& Items = this->Items;
	Items[InSlot] = InItem;

#if !(WITH_NETWORKING)
	// If networking is off, the fast array serializer isnt used so OnItemAdded is never fired
	OnItemAdded.Broadcast(InItem, InSlot);
#endif

	return true;
}

bool UContainerInstanceComponent::AddItem_MP(UContainerInstanceAccessor* InAccessor, const FItemInstance& InItem, int32 InSlot /*= -1*/)
{
	InAccessor->Server_AddItem(this, InItem, InSlot);
	return false;
}

void UContainerInstanceComponent::RemoveItem_Implementation(int32 InSlot)
{
	if (!IsSlotOccupied(InSlot))
		return;

	TArray<FItemInstance>& Items = this->Items;
	FItemInstance& Item = Items[InSlot];
	Items.RemoveAt(InSlot, 1, false);
	Items[InSlot] = UNullItem::GetInstance();

#if !(WITH_NETWORKING)
	// If networking is off, the fast array serializer isnt used so OnItemRemoved is never fired
	OnItemRemoved.Broadcast(InItem, InSlot);
#endif
}

void UContainerInstanceComponent::RemoveItem_MP(UContainerInstanceAccessor* InAccessor, int32 InSlot)
{
	InAccessor->Server_RemoveItem(this, InSlot);
}

void UContainerInstanceComponent::SwapItems_Implementation(int32 InSourceSlot, int32 InDestinationSlot)
{
	if (!IsSlotOccupied(InSourceSlot))
		return;

#if !(WITH_NETWORKING)
	OnItemRemoved.Broadcast(Items[InSourceSlot], InSourceSlot);
	OnItemRemoved.Broadcast(Items[InDestinationSlot], InDestinationSlot);
#endif

	TArray<FItemInstance>& Items = this->Items;
	Items.Swap(InSourceSlot, InDestinationSlot);

#if !(WITH_NETWORKING)
	OnItemAdded.Broadcast(Items[InSourceSlot], InSourceSlot);
	OnItemAdded.Broadcast(Items[InDestinationSlot], InDestinationSlot);
#endif
}

void UContainerInstanceComponent::SwapItems_MP(UContainerInstanceAccessor* InAccessor, int32 InSourceSlot, int32 InDestinationSlot)
{
	InAccessor->Server_SwapItems(this, InSourceSlot, InDestinationSlot);
}

bool UContainerInstanceComponent::TransferItem_Implementation(int32 InSourceSlot, UContainerInstanceComponent* InDestinationContainer, int32 InDestinationSlot)
{
	if (InDestinationContainer->IsSlotOccupied(InDestinationSlot) || !IsSlotOccupied(InSourceSlot))
		return false;

	TArray<FItemInstance>& Items = this->Items;
	FItemInstance SourceItem = Items[InSourceSlot];

	return InDestinationContainer->AddItem(SourceItem, InDestinationSlot);
}

bool UContainerInstanceComponent::TransferItem_MP(UContainerInstanceAccessor* InAccessor, int32 InSourceSlot, UContainerInstanceComponent* InDestinationContainer, int32 InDestinationSlot)
{
	InAccessor->Server_TransferItem(this, InSourceSlot, InDestinationContainer, InDestinationSlot);

	return false;
}

void UContainerInstanceComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UContainerInstanceComponent, Items);
}

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