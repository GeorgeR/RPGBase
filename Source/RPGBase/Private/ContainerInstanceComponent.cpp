#include "ContainerInstanceComponent.h"
#include "UnrealNetwork.h"
#include "GameFramework/Actor.h"

UContainerInstanceComponent::UContainerInstanceComponent()
{
	CachedContainer = nullptr;

	if (ContainerClass.IsValid())
		SetContainerClass(ContainerClass);
}

void UContainerInstanceComponent::SetContainerClass(FSoftClassPath& InContainerClass)
{
	ContainerClass = InContainerClass;

	Items.Init(UNullItem::GetInstance(), GetCapacity());
}

bool UContainerInstanceComponent::CanAddItem_Implementation(const FItemInstance& InItem, int32 InSlot)
{
	if (InSlot == -1)
		InSlot = GetFirstAvailableSlot();

	return !IsSlotOccupied(InSlot);
}

/* By default, this won't add the item if the slot is occupied. You might customize it to swap items with the source. */
bool UContainerInstanceComponent::AddItem_Implementation(const FItemInstance& InItem, int32 InSlot)
{
	if (!CanAddItem(InItem, InSlot))
		return false;

	Items[InSlot] = InItem;

#if !(WITH_NETWORKING)
	// If networking is off, the fast array serializer isnt used so OnItemAdded is never fired
	OnItemAdded.Broadcast(InItem, InSlot);
#endif

	return true;
}

bool UContainerInstanceComponent::AddItem_MP(UContainerInstanceAccessor* InAccessor, const FItemInstance& InItem, const int32 InSlot /*= -1*/)
{
	InAccessor->Server_AddItem(this, InItem, InSlot);
	return false;
}

void UContainerInstanceComponent::RemoveItem_Implementation(const int32 InSlot)
{
	if (!IsSlotOccupied(InSlot))
		return;

	auto& Item = Items[InSlot];
	Items.RemoveAt(InSlot, 1, false);
	Items[InSlot] = UNullItem::GetInstance();

#if !(WITH_NETWORKING)
	// If networking is off, the fast array serializer isnt used so OnItemRemoved is never fired
	OnItemRemoved.Broadcast(InItem, InSlot);
#endif
}

void UContainerInstanceComponent::RemoveItem_MP(UContainerInstanceAccessor* InAccessor, const int32 InSlot)
{
	InAccessor->Server_RemoveItem(this, InSlot);
}

void UContainerInstanceComponent::SwapItems_Implementation(const int32 InSourceSlot, const int32 InDestinationSlot)
{
	if (!IsSlotOccupied(InSourceSlot))
		return;

#if !(WITH_NETWORKING)
	OnItemRemoved.Broadcast(Items[InSourceSlot], InSourceSlot);
	OnItemRemoved.Broadcast(Items[InDestinationSlot], InDestinationSlot);
#endif

	Items.Swap(InSourceSlot, InDestinationSlot);

#if !(WITH_NETWORKING)
	OnItemAdded.Broadcast(Items[InSourceSlot], InSourceSlot);
	OnItemAdded.Broadcast(Items[InDestinationSlot], InDestinationSlot);
#endif
}

void UContainerInstanceComponent::SwapItems_MP(UContainerInstanceAccessor* InAccessor, const int32 InSourceSlot, const int32 InDestinationSlot)
{
	InAccessor->Server_SwapItems(this, InSourceSlot, InDestinationSlot);
}

bool UContainerInstanceComponent::TransferItem_Implementation(const int32 InSourceSlot, UContainerInstanceComponent* InDestinationContainer, const int32 InDestinationSlot)
{
	if (InDestinationContainer->IsSlotOccupied(InDestinationSlot) || !IsSlotOccupied(InSourceSlot))
		return false;

	const auto SourceItem = Items[InSourceSlot];

	return InDestinationContainer->AddItem(SourceItem, InDestinationSlot);
}

bool UContainerInstanceComponent::TransferItem_MP(UContainerInstanceAccessor* InAccessor, const int32 InSourceSlot, UContainerInstanceComponent* InDestinationContainer, const int32 InDestinationSlot)
{
	InAccessor->Server_TransferItem(this, InSourceSlot, InDestinationContainer, InDestinationSlot);

	return false;
}

void UContainerInstanceComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UContainerInstanceComponent, Id);
	DOREPLIFETIME(UContainerInstanceComponent, OwnerId);
}

int32 UContainerInstanceComponent::GetFirstAvailableSlot()
{
	for (auto i = 0; i < Items.Num(); i++)
	{
		if (Items[i].IsNullItem())
			return i;
	}

	return -1;
}

bool UContainerInstanceComponent::IsSlotOccupied(const int32 InSlot)
{
	return IsSlotInRange(InSlot) && !Items[InSlot].IsNullItem();
}

const UContainer* UContainerInstanceComponent::GetContainer()
{
	if (!ContainerClass.IsValid())
		return nullptr;

	if(CachedContainer == nullptr)
	{
		const auto Class = ContainerClass.TryLoadClass<UContainer>();
		if(Class != nullptr)
			CachedContainer = Cast<UContainer>(Class->GetDefaultObject());
	}

	return CachedContainer;
}