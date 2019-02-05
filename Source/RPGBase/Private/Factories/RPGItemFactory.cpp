#include "RPGItemFactory.h"

#include "RPGItem.h"
#include "Engine/World.h"
#include "UniqueIdFactory.h"

URPGItemFactory::URPGItemFactory()
{
	UniqueIdFactory = CreateDefaultSubobject<UUniqueIdFactory>(TEXT("UniqueIdFactory"));
}

bool URPGItemFactory::CreateInstance_Implementation(TSubclassOf<URPGItem> ItemClass, int32 Count, TArray<FRPGItemInstance>& ItemInstances)
{
	check(ItemClass != nullptr);
	if (Count <= 0) return false;

	ItemInstances.Empty();

	auto Item = Cast<URPGItem>(ItemClass->GetDefaultObject());
	check(Item);

	if(Count == 1 || Item->bIsStackable)
	{
		FRPGItemInstance Result;
		Result.Id = UniqueIdFactory->GetNewId(TEXT("ItemInstance"));
		Result.ItemClass = FSoftClassPath(ItemClass);
		Result.StackSize = Count;
		ItemInstances.Add(Result);
		return true;
	}

	for(auto i = 0; i < Count; i++)
	{
		FRPGItemInstance Result;
		Result.Id = UniqueIdFactory->GetNewId(TEXT("ItemInstance"));
		Result.ItemClass = FSoftClassPath(ItemClass);
		Result.StackSize = 1;
		ItemInstances.Add(Result);
	}

	return ItemInstances.Num() == Count;
}

bool URPGItemFactory::CreateActorFor_Implementation(UObject* WorldContextObject, const FRPGItemInstance& ItemInstance, AActor* Actor)
{
	check(WorldContextObject);
	check(WorldContextObject->GetWorld());
	
	auto World = WorldContextObject->GetWorld();

	AActor* Result = World->SpawnActor<AActor>();
	Actor = Result;

	return Result != nullptr;
}

bool URPGItemFactory::LoadInstance_Implementation(const FString& Id, FRPGItemInstance& ItemInstance)
{
	// TODO: Load from persistent store and write data to instance

	return true;
}
