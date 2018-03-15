#include "ItemInstance.h"
#include "Item.h"
#include "ContainerInstanceComponent.h"

FItemInstance::FItemInstance(const FItemInstance& InSource)
{
	CachedItem = nullptr;

	Id = InSource.Id; // TODO: Id should be new
	ItemClass = InSource.ItemClass;
	ContainerId = InSource.ContainerId;
	StackSize = InSource.StackSize;
	ItemClass = InSource.ItemClass;
}

bool FItemInstance::IsNullItem()
{
	return GetItem()->GetClass() == UNullItem::StaticClass();
}

int32 FItemInstance::AddToStack(const int32 InAmount)
{
	const auto Item = GetItem();
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
	const auto Item = GetItem();
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

UItem* FItemInstance::GetItem()
{
	if (!ItemClass.IsValid())
		return nullptr;

	if(CachedItem == nullptr)
	{
		const auto Class = ItemClass.TryLoadClass<UItem>();
		if (Class != nullptr)
			CachedItem = Cast<UItem>(Class->GetDefaultObject());
	}

	return CachedItem;
}

void FItemInstanceArray::RegisterWithOwner(class UContainerInstanceComponent* InOwner) { Owner = InOwner; }