#include "ItemFactory.h"
#include "Item.h"
#include "Engine/World.h"
#include "UniqueIdFactory.h"

UItemFactory::UItemFactory()
{
	UniqueIdFactory = CreateDefaultSubobject<UUniqueIdFactory>(TEXT("UniqueIdFactory"));
}

bool UItemFactory::CreateInstance_Implementation(TSubclassOf<UItem> ItemClass, int32 Count, TArray<FItemInstance>& ItemInstances)
{
	check(ItemClass != nullptr);
	if (Count <= 0) return false;

	ItemInstances.Empty();

	auto Item = Cast<UItem>(ItemClass->GetDefaultObject());
	check(Item);

	if(Count == 1 || Item->bIsStackable)
	{
		FItemInstance Result;
		Result.Id = UniqueIdFactory->GetNewId(TEXT("ItemInstance"));
		Result.ItemClass = FSoftClassPath(ItemClass);
		Result.StackSize = Count;
		ItemInstances.Add(Result);
		return true;
	}

	for(auto i = 0; i < Count; i++)
	{
		FItemInstance Result;
		Result.Id = UniqueIdFactory->GetNewId(TEXT("ItemInstance"));
		Result.ItemClass = FSoftClassPath(ItemClass);
		Result.StackSize = 1;
		ItemInstances.Add(Result);
	}

	return ItemInstances.Num() == Count;
}

bool UItemFactory::CreateActorFor_Implementation(UObject* WorldContextObject, const FItemInstance& ItemInstance, AActor* Actor)
{
	check(WorldContextObject);
	check(WorldContextObject->GetWorld());
	
	auto World = WorldContextObject->GetWorld();

	AActor* Result = World->SpawnActor<AActor>();
	Actor = Result;

	return Result != nullptr;
}

bool UItemFactory::LoadInstance_Implementation(const FString& Id, FItemInstance& ItemInstance)
{
	// TODO: Load from persistent store and write data to instance

	return true;
}
