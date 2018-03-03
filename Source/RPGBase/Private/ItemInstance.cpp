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

#if WITH_NETWORKING
void FItemInstance::PreReplicatedRemove(const struct FItemInstanceArray& InArraySerializer)
{
	if (InArraySerializer.Owner != nullptr)
		InArraySerializer.Owner->OnItemRemoved(*this);
}

void FItemInstance::PostReplicatedAdd(const struct FItemInstanceArray& InArraySerializer)
{
	if (InArraySerializer.Owner != nullptr)
		InArraySerializer.Owner->OnItemAdded(*this);
}
#endif

TSubclassOf<UItem> FItemInstance::GetItemClass()
{
	if (ItemClass == nullptr)
		ItemClass = Item.TryLoadClass<UItem>();

	check(ItemClass);

	return ItemClass;
}

void FItemInstanceArray::RegisterWithOwner(class UContainerInstanceComponent* InOwner){ Owner = InOwner; }
