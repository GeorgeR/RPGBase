#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/NetSerialization.h"

#include "ItemInstance.generated.h"

/* An instance of an item that shows in an inventory/container, etc. */
/* Why? More lightweight than instancing the full object everywhere. */
USTRUCT(BlueprintType)
struct RPGBASE_API FItemInstance
	: public FFastArraySerializerItem
{
	GENERATED_BODY()

public:
	FItemInstance() { }
	FItemInstance(const FItemInstance& InSource);
	virtual ~FItemInstance() { }

	/* Unique Id of the instance */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName Id;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FSoftClassPath Item;

	/* Id of the owning container, ie. an inventory or the world. */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName ContainerId;

	/* Current stack size, limited by Item's MaxStackSize */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 StackSize;

	bool IsNullItem();

	/* Returns the amount actually added to the stack (ie. if it was beyond capacity). You might customize this to add another item with the remaining amount. */
	virtual int32 AddToStack(int32 InAmount);

	/* Returns amount actually removed. */
	virtual int32 RemoveFromStack(int32 InAmount);

	virtual FItemInstance SplitStack(int32 InAmount);

	virtual FItemInstance Clone(int32 InStackSize);

	void PreReplicatedRemove(const struct FItemInstanceArray& InArraySerializer);
	void PostReplicatedAdd(const struct FItemInstanceArray& InArraySerializer);

	bool operator==(const FItemInstance& InOther) const;

private:
	UPROPERTY()
	TSubclassOf<class UItem> ItemClass;

	TSubclassOf<class UItem> GetItemClass();
};

/* Remember to call MarkArrayDirty if an item is removed,
MarkItemDirty if added or item changed. */
USTRUCT(BlueprintType)
struct RPGBASE_API FItemInstanceArray
	: public FFastArraySerializer
{
	GENERATED_BODY()

public:
	class UContainerInstanceComponent* Owner;

	void RegisterWithOwner(class UContainerInstanceComponent* InOwner);

	/* Access this as though it were the array itself */
	operator TArray<FItemInstance>&() { return Items; }
	
	bool NetDeltaSerialize(FNetDeltaSerializeInfo & DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FItemInstance, FItemInstanceArray>(Items, DeltaParms, *this);
	}

private:
	friend struct FItemInstance;

	UPROPERTY()
	TArray<FItemInstance> Items;
};

template<>
struct TStructOpsTypeTraits<FItemInstanceArray>
	: public TStructOpsTypeTraitsBase2<FItemInstanceArray>
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};