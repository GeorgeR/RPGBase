#include "Item.h"

UNullItem::UNullItem()
{
	Name = TEXT("None");
}

UNullItem* UNullItem::Get()
{
	static UNullItem* Instance = nullptr;
	if (Instance == nullptr)
		Instance = NewObject<UNullItem>(nullptr);

	return Instance;
}

FItemInstance& UNullItem::GetInstance()
{
	static FItemInstance Instance;
	Instance.ItemClass = FSoftClassPath(Get()->GetClass());
	return Instance;
}