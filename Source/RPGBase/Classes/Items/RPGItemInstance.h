#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/NetSerialization.h"

#include "RPGItemInstance.generated.h"

class URPGItem;

/* An instance of an item that shows in an inventory/container, etc. */
/* Why? More lightweight than instancing the full object everywhere. */
/* Ownership: The item isn't owned, it's container is */
USTRUCT(BlueprintType)
struct RPGBASE_API FRPGItemInstance
	: public FFastArraySerializerItem
{
	GENERATED_BODY()

public:
	FRPGItemInstance();
	FRPGItemInstance(const FRPGItemInstance& InSource);

	/** @bug this causes crash */
	virtual ~FRPGItemInstance() = default;

	/* Unique Id of the instance */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item")
	FString Id;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item")
	TSoftClassPtr<URPGItem> ItemClass;

	/* Id of the owning container, ie. an inventory or the world. */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item")
	FString ContainerId;

	/* Current stack size, limited by Item's MaxStackSize */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item")
	int32 StackSize;

	URPGItem* GetItem() const;

	/* Returns the amount actually added to the stack (ie. if it was beyond capacity). You might customize this to add another item with the remaining amount. */
	virtual int32 AddToStack(int32 Amount);

	// #todo If resulting stack size is 0, destroy the item
	/* Returns amount actually removed. */
	virtual int32 RemoveFromStack(int32 Amount);

	virtual FRPGItemInstance SplitStack(int32 Amount);

	virtual FRPGItemInstance Clone(int32 InStackSize);

	static FIntPoint GetIndex2D(int32 ColumnCount, int32 Slot);

	void PreReplicatedRemove(const struct FItemInstanceArray& ArraySerializer) const;
	void PostReplicatedAdd(const struct FItemInstanceArray& ArraySerializer) const;

	bool operator==(const FRPGItemInstance& Other) const;
	bool operator!=(const FRPGItemInstance& Other) const;

	friend inline uint32 GetTypeHash(const FRPGItemInstance& Value)
	{
		return GetTypeHash(Value.Id);
	}

	inline bool IsValid() const { return Id != TEXT("Invalid"); }
};

template<>
struct TStructOpsTypeTraits<FRPGItemInstance>
	: public TStructOpsTypeTraitsBase2<FRPGItemInstance>
{
	enum
	{
		WithNoDestructor = true,
	};
};

/* Remember to call MarkArrayDirty if an item is removed,
MarkItemDirty if added or item changed. */
USTRUCT(BlueprintType)
struct RPGBASE_API FItemInstanceArray
	: public FFastArraySerializer
{
	GENERATED_BODY()

public:
	class URPGContainerInstanceComponent* Owner;

	void RegisterWithOwner(class URPGContainerInstanceComponent* InOwner);

	/* Access this as though it were the array itself */
	operator TArray<FRPGItemInstance>&() { return Items; }
	
	bool NetDeltaSerialize(FNetDeltaSerializeInfo & DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FRPGItemInstance, FItemInstanceArray>(Items, DeltaParms, *this);
	}

private:
	friend struct FRPGItemInstance;

	UPROPERTY()
	TArray<FRPGItemInstance> Items;
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
