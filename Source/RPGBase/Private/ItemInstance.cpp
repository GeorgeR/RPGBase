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

int32 FItemInstance::AddToStack(const int32 InAmount)
{
	const auto Item = GetItemClass()->GetDefaultObject<UItem>();
	check(Item);

	const auto Remainder = FMath::Abs(Item->MaxStackSize - (StackSize + InAmount));
	auto Added = InAmount - Remainder;
	Added = FMath::Max(Added, 0); // Clamp to 0

	StackSize += Added;

	return Added;
}

int32 FItemInstance::RemoveFromStack(const int32 InAmount)
{
	auto Removed = FMath::Min(StackSize, StackSize - InAmount);
	Removed = FMath::Max(Removed, 0); // Clamp to 0

	StackSize -= Removed;

	return Removed;
}

FItemInstance FItemInstance::SplitStack(const int32 InAmount)
{
	const auto Item = GetItemClass()->GetDefaultObject<UItem>();
	check(Item);

	const auto Remainder = FMath::Abs(Item->MaxStackSize - (StackSize + InAmount));

	auto NewItem = Clone(Remainder);
	return NewItem;
}

FItemInstance FItemInstance::Clone(const int32 InStackSize)
{
	auto Result(*this);
	Result.StackSize = InStackSize;
	return Result;
}

UItem* FItemInstance::LoadDefaultItem()
{
	return GetItemClass().GetDefaultObject();
}

FIntPoint FItemInstance::GetIndex2D(const int32 InColumnCount, const int32 InSlot)
{
	FIntPoint Result;
	Result.X = InSlot % InColumnCount;
	Result.Y = InSlot / InColumnCount;
	return Result;
}

void FItemInstance::PreReplicatedRemove(const struct FItemInstanceArray& InArraySerializer) const
{
	/* Note that as per the documentation, the order of items is different on the Client and Server.
	It doesn't matter, the index of for client-side UI effects. */
	if (InArraySerializer.Owner != nullptr)
	{
		const auto Index = InArraySerializer.Items.IndexOfByKey(*this);
		InArraySerializer.Owner->OnItemRemoved.Broadcast(*this, Index);
	}
}

void FItemInstance::PostReplicatedAdd(const struct FItemInstanceArray& InArraySerializer) const
{
	/* Note that as per the documentation, the order of items is different on the Client and Server. 
	It doesn't matter, the index of for client-side UI effects. */
	if (InArraySerializer.Owner != nullptr)
	{
		const auto Index = InArraySerializer.Items.IndexOfByKey(*this);
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

void FItemInstanceArray::RegisterWithOwner(class UContainerInstanceComponent* InOwner) { Owner = InOwner; }