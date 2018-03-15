#include "ItemFactory.h"
#include "Item.h"

bool UItemFactory::CreateInstance_Implementation(TSubclassOf<UItem> InItemClass, int32 InCount, TArray<FItemInstance>& OutItemInstances)
{
	check(InItemClass != nullptr);
	if (InCount <= 0) return false;

	OutItemInstances.Empty();

	auto Item = Cast<UItem>(InItemClass->GetDefaultObject());
	check(Item);

	if(InCount == 1 || Item->bIsStackable)
	{
		FItemInstance Result;
		// TODO: Set ItemInstance Id
		Result.ItemClass = FSoftClassPath(InItemClass);
		Result.StackSize = InCount;
		OutItemInstances.Add(Result);
		return true;
	}

	for(auto i = 0; i < InCount; i++)
	{
		FItemInstance Result;
		// TODO: Set ItemInstance Id
		Result.ItemClass = FSoftClassPath(InItemClass);
		Result.StackSize = 1;
		OutItemInstances.Add(Result);
	}

	return OutItemInstances.Num() == InCount;
}

bool UItemFactory::CreateActorFor_Implementation(UObject* InWorldContextObject, FItemInstance& InItemInstance, AActor* OutActor)
{
	check(InWorldContextObject);
	check(InWorldContextObject->GetWorld());

	auto World = InWorldContextObject->GetWorld();

	AActor* Result = World->SpawnActor<AActor>();

	OutActor = Result;

	return Result != nullptr;
}