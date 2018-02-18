#include "Item.h"

int32 UItem::AddToStack_Implementation(int32 InAmount)
{
	int32 Remainder = FMath::Abs(MaxStackSize - (StackSize + InAmount));
	int32 Added = InAmount - Remainder;
	Added = FMath::Max(Added, 0); // Clamp to 0

	StackSize += Added;

	return Added;
}

int32 UItem::RemoveFromStack_Implementation(int32 InAmount)
{
	int32 Removed = FMath::Min(StackSize, StackSize - InAmount);
	Removed = FMath::Max(Removed, 0); // Clamp to 0

	StackSize -= Removed;

	return Removed;
}

UItem* UItem::SplitStack_Implementation(int32 InAmount)
{
	int32 Remainder = FMath::Abs(MaxStackSize - (StackSize + InAmount));

	UItem* NewItem = Clone(Remainder);

	return NewItem;
}

UItem* UItem::Clone_Implementation(int32 InStackSize)
{
	if (this->GetClass() == UNullItem::StaticClass())
		return UNullItem::Get();

	UItem* NewItem = DuplicateObject<UItem>(this, nullptr);
	NewItem->StackSize = InStackSize;
	
	return NewItem;
}

UNullItem::UNullItem()
{
	static FName NullName = TEXT("Null");
	Name = NullName;

	MaxStackSize = 0;
}

UNullItem* UNullItem::Get()
{
	static UNullItem* Instance = nullptr;
	if (Instance == nullptr)
		Instance = NewObject<UNullItem>();

	return Instance;
}