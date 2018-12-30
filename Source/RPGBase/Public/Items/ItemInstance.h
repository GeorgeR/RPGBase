#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/NetSerialization.h"

#include "ItemInstance.generated.h"

class UItem;

/* An instance of an item that shows in an inventory/container, etc. */
/* Why? More lightweight than instancing the full object everywhere. */
/* Ownership: The item isn't owned, it's container is */
USTRUCT(BlueprintType)
struct RPGBASE_API FItemInstance
	: public FFastArraySerializerItem
{
	GENERATED_BODY()

public:
	FItemInstance() : Id(TEXT("Invalid")) { }
	FItemInstance(const FItemInstance& InSource);
	virtual ~FItemInstance() = default;

	/* Unique Id of the instance */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString Id;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSoftClassPtr<UItem> ItemClass;

	/* Id of the owning container, ie. an inventory or the world. */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString ContainerId;

	/* Current stack size, limited by Item's MaxStackSize */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 StackSize;

	UItem* GetItem();

	/* Returns the amount actually added to the stack (ie. if it was beyond capacity). You might customize this to add another item with the remaining amount. */
	virtual int32 AddToStack(int32 Amount);

	/* Returns amount actually removed. */
	virtual int32 RemoveFromStack(int32 Amount);

	virtual FItemInstance SplitStack(int32 Amount);

	virtual FItemInstance Clone(int32 StackSize);

	static FIntPoint GetIndex2D(int32 ColumnCount, int32 Slot);

	void PreReplicatedRemove(const struct FItemInstanceArray& ArraySerializer) const;
	void PostReplicatedAdd(const struct FItemInstanceArray& ArraySerializer) const;

	bool operator==(const FItemInstance& Other) const;
	bool operator!=(const FItemInstance& Other) const;

	friend inline uint32 GetTypeHash(const FItemInstance& Value)
	{
		return GetTypeHash(Value.Id);
	}

	inline bool IsValid() const { return Id != TEXT("Invalid"); }

private:
	UPROPERTY(Transient)
	class UItem* CachedItem;
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
