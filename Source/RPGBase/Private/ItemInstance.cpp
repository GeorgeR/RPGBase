#include "ItemInstance.h"
#include "Item.h"
#include "ContainerInstanceComponent.h"

FItemInstance::FItemInstance(const FItemInstance& InSource)
{
	Id = InSource.Id; // TODO: Id should be new
	Item = InSource.Item;
	ContainerId = InSource.ContainerId;
	StackSize = InSource.StackSize;
	ItemClass = InSource.ItemClass;
}

bool FItemInstance::IsNullItem()
{
	return GetItemClass()->GetDefaultObject<UNullItem>() != nullptr;
}

int32 FItemInstance::AddToStack(int32 InAmount)
{
	UItem* Item = GetItemClass()->GetDefaultObject<UItem>();
	check(Item);

	int32 Remainder = FMath::Abs(Item->MaxStackSize - (StackSize + InAmount));
	int32 Added = InAmount - Remainder;
	Added = FMath::Max(Added, 0); // Clamp to 0

	StackSize += Added;

	return Added;
}

int32 FItemInstance::RemoveFromStack(int32 InAmount)
{
	int32 Removed = FMath::Min(StackSize, StackSize - InAmount);
	Removed = FMath::Max(Removed, 0); // Clamp to 0

	StackSize -= Removed;

	return Removed;
}

FItemInstance FItemInstance::SplitStack(int32 InAmount)
{
	UItem* Item = GetItemClass()->GetDefaultObject<UItem>();
	check(Item);

	int32 Remainder = FMath::Abs(Item->MaxStackSize - (StackSize + InAmount));

	FItemInstance NewItem = Clone(Remainder);
	return NewItem;
}

FItemInstance FItemInstance::Clone(int32 InStackSize)
{
	FItemInstance Result(*this);
	Result.StackSize = InStackSize;
	return Result;
}

void FItemInstance::PreReplicatedRemove(const struct FItemInstanceArray& InArraySerializer)
{
	/* Note that as per the documentation, the order of items is different on the Client and Server.
	It doesn't matter, the index of for client-side UI effects. */
	if (InArraySerializer.Owner != nullptr)
	{
		int32 Index = InArraySerializer.Items.IndexOfByKey(*this);
		InArraySerializer.Owner->OnItemRemoved.Broadcast(*this, Index);
	}
}

void FItemInstance::PostReplicatedAdd(const struct FItemInstanceArray& InArraySerializer)
{
	/* Note that as per the documentation, the order of items is different on the Client and Server. 
	It doesn't matter, the index of for client-side UI effects. */
	if (InArraySerializer.Owner != nullptr)
	{
		int32 Index = InArraySerializer.Items.IndexOfByKey(*this);
		InArraySerializer.Owner->OnItemAdded.Broadcast(*this, Index);
	}
}

bool FItemInstance::operator==(const FItemInstance& InOther) const { return Id == InOther.Id; }

TSubclassOf<UItem> FItemInstance::GetItemClass()
{
	if (ItemClass == nullptr)
		ItemClass = Item.TryLoadClass<UItem>();

	check(ItemClass);

	return ItemClass;
}

void FItemInstanceArray::RegisterWithOwner(class UContainerInstanceComponent* InOwner){ Owner = InOwner; }
