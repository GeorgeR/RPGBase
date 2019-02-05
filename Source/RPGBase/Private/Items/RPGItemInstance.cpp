#include "RPGItemInstance.h"

#include "RPGItem.h"
#include "ContainerInstanceComponent.h"

FRPGItemInstance::FRPGItemInstance()
	: Id(TEXT("Invalid")),
	ItemClass(nullptr),
	ContainerId(TEXT("")),
	StackSize(0),
	CachedItem(nullptr) { }

FRPGItemInstance::FRPGItemInstance(const FRPGItemInstance& Source)
{
	CachedItem = nullptr;

	Id = Source.Id; // TODO: Id should be new
	ItemClass = Source.ItemClass;
	ContainerId = Source.ContainerId;
	StackSize = Source.StackSize;
	ItemClass = Source.ItemClass;
}

int32 FRPGItemInstance::AddToStack(const int32 Amount)
{
	const auto Item = GetItem();
	check(Item);

	const auto Remainder = FMath::Abs(Item->MaxStackSize - (StackSize + Amount));
	auto Added = Amount - Remainder;
	Added = FMath::Max(Added, 0); // Clamp to 0

	StackSize += Added;

	return Added;
}

int32 FRPGItemInstance::RemoveFromStack(const int32 Amount)
{
	auto Removed = FMath::Min(StackSize, StackSize - Amount);
	Removed = FMath::Max(Removed, 0); // Clamp to 0

	StackSize -= Removed;

	return Removed;
}

FRPGItemInstance FRPGItemInstance::SplitStack(const int32 Amount)
{
	const auto Item = GetItem();
	check(Item);

	const auto Remainder = FMath::Abs(Item->MaxStackSize - (StackSize + Amount));

	auto NewItem = Clone(Remainder);
	return NewItem;
}

FRPGItemInstance FRPGItemInstance::Clone(const int32 StackSize)
{
	auto Result(*this);
	Result.StackSize = StackSize;
	return Result;
}

FIntPoint FRPGItemInstance::GetIndex2D(const int32 ColumnCount, const int32 Slot)
{
	FIntPoint Result;
	Result.X = Slot % ColumnCount;
	Result.Y = Slot / ColumnCount;
	return Result;
}

void FRPGItemInstance::PreReplicatedRemove(const struct FItemInstanceArray& ArraySerializer) const
{
	/* Note that as per the documentation, the order of items is different on the Client and Server.
	It doesn't matter, the index of for client-side UI effects. */
	if (ArraySerializer.Owner != nullptr)
	{
		const auto Index = ArraySerializer.Items.IndexOfByKey(*this);
		ArraySerializer.Owner->OnItemRemoved.Broadcast(*this, Index);
	}
}

void FRPGItemInstance::PostReplicatedAdd(const struct FItemInstanceArray& ArraySerializer) const
{
	/* Note that as per the documentation, the order of items is different on the Client and Server. 
	It doesn't matter, the index of for client-side UI effects. */
	if (ArraySerializer.Owner != nullptr)
	{
		const auto Index = ArraySerializer.Items.IndexOfByKey(*this);
		ArraySerializer.Owner->OnItemAdded.Broadcast(*this, Index);
	}
}

bool FRPGItemInstance::operator==(const FRPGItemInstance& Other) const { return Id == Other.Id; }
bool FRPGItemInstance::operator!=(const FRPGItemInstance& Other) const { return !(*this == Other); }

URPGItem* FRPGItemInstance::GetItem()
{
	if (!ItemClass.IsValid())
		return nullptr;

	if(CachedItem == nullptr)
	{
		const auto Class = ItemClass.LoadSynchronous();
		if (Class != nullptr)
			CachedItem = Cast<URPGItem>(Class->GetDefaultObject());
	}

	return CachedItem;
}

void FItemInstanceArray::RegisterWithOwner(class UContainerInstanceComponent* Owner) { this->Owner = Owner; }
