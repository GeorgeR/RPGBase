#include "Items/RPGContainerInstanceComponent.h"

#include "UnrealNetwork.h"
#include "GameFramework/Actor.h"

#include "Items/RPGContainerInstanceProxyComponent.h"

URPGContainerInstanceComponent::URPGContainerInstanceComponent()
	: CachedContainer(nullptr)
{
	if (ContainerClass.IsValid())
		SetContainerClass(ContainerClass);
}

void URPGContainerInstanceComponent::SetContainerClass(FSoftClassPath& InContainerClass)
{
	if (ContainerClass == InContainerClass)
		return;

	ContainerClass = InContainerClass;

	Items.Empty(GetCapacity());
}

bool URPGContainerInstanceComponent::CanAddItem_Implementation(const TScriptInterface<IRPGUserInterface>& Instigator, const FRPGItemInstance& Item, int32 Slot)
{
	if (Slot == -1)
		Slot = GetFirstAvailableSlot();

	return !IsSlotOccupied(Slot);
}

/* By default, this won't add the item if the slot is occupied. You might customize it to swap items with the source. */
bool URPGContainerInstanceComponent::AddItem_Implementation(const TScriptInterface<IRPGUserInterface>& Instigator, const FRPGItemInstance& Item, int32 Slot)
{
	if (!CanAddItem(Instigator, Item, Slot))
		return false;

	Items[Slot] = Item;

#if !(WITH_NETWORKING)
	// If networking is off, the fast array serializer isnt used so OnItemAdded is never fired
	OnItemAdded.Broadcast(Item, Slot);
#endif

	return true;
}

void URPGContainerInstanceComponent::RemoveItem_Implementation(const TScriptInterface<IRPGUserInterface>& Instigator, const int32 Slot)
{
	if (!IsSlotOccupied(Slot))
		return;

	auto& Item = Items[Slot];
	Items.RemoveAt(Slot, 1, false);
	// TODO
	//Items[InSlot] = UNullItem::GetInstance();

#if !(WITH_NETWORKING)
	// If networking is off, the fast array serializer isnt used so OnItemRemoved is never fired
	OnItemRemoved.Broadcast(InItem, Slot);
#endif
}

void URPGContainerInstanceComponent::SwapItems_Implementation(const TScriptInterface<IRPGUserInterface>& Instigator, const int32 SourceSlot, const int32 DestinationSlot)
{
	if (!IsSlotOccupied(SourceSlot))
		return;

#if !(WITH_NETWORKING)
	OnItemRemoved.Broadcast(Items[SourceSlot], SourceSlot);
	OnItemRemoved.Broadcast(Items[DestinationSlot], DestinationSlot);
#endif

	Items.Swap(SourceSlot, DestinationSlot);

#if !(WITH_NETWORKING)
	OnItemAdded.Broadcast(Items[SourceSlot], SourceSlot);
	OnItemAdded.Broadcast(Items[DestinationSlot], DestinationSlot);
#endif
}

bool URPGContainerInstanceComponent::TransferItem_Implementation(const TScriptInterface<IRPGUserInterface>& Instigator, const int32 SourceSlot, URPGContainerInstanceComponent* DestinationContainer, const int32 DestinationSlot)
{
	if (DestinationContainer->IsSlotOccupied(DestinationSlot) || !IsSlotOccupied(SourceSlot))
		return false;

	const auto SourceItem = Items[SourceSlot];

	return DestinationContainer->AddItem(Instigator, SourceItem, DestinationSlot);
}

void URPGContainerInstanceComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URPGContainerInstanceComponent, Id);
	DOREPLIFETIME(URPGContainerInstanceComponent, Owner);
}

int32 URPGContainerInstanceComponent::GetFirstAvailableSlot()
{
	for (auto i = 0; i < Items.Num(); i++)
	{
		if (!Items[i].IsValid())
			return i;
	}

	return -1;
}

bool URPGContainerInstanceComponent::IsSlotOccupied(const int32 Slot)
{
	return IsSlotInRange(Slot) && Items[Slot].IsValid();
}

const URPGContainer* URPGContainerInstanceComponent::GetContainer()
{
	if (!ContainerClass.IsValid())
		return nullptr;

	if(CachedContainer == nullptr)
	{
		const auto Class = ContainerClass.TryLoadClass<URPGContainer>();
		if(Class != nullptr)
			CachedContainer = Cast<URPGContainer>(Class->GetDefaultObject());
	}

	return CachedContainer;
}
