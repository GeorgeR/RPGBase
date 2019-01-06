#pragma once

#include "CoreMinimal.h"
#include "Engine/NetSerialization.h"
#include "AssociationMember.h"

#include "AssociationMemberArray.generated.h"

USTRUCT(BlueprintType)
struct RPGBASE_API FAssociationMemberArray
	: public FFastArraySerializer
{
	GENERATED_BODY()

public:
	FAssociationMemberArray();

	FORCEINLINE int32 Add(FAssociationMember& Item)
	{
		auto Result = Items.Add(Item);
		MarkItemDirty(Item);
		return Result;
	}

	int32 Remove(const FAssociationMember& Item)
	{
		auto Result = Items.Remove(Item);
		MarkArrayDirty();
		return Result;
	}
	
	void RegisterWithOwner(class UAssociation* Owner);

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms);

	template <typename TElementType, typename TSerializerType>
	bool ShouldWriteFastArrayItem(const TElementType& Item, const bool bIsWritingOnClient)
	{
		if (bIsWritingOnClient)
			return Item.ReplicationID != INDEX_NONE;

		return true;
	}

	/* Access this as though it were the array itself */
	operator TArray<FAssociationMember>&() { return Items; }

private:
	friend struct FAssociationMember;

	UPROPERTY()
	UAssociation* Owner;

	UPROPERTY()
	TArray<FAssociationMember> Items;
};

template<>
struct TStructOpsTypeTraits<FAssociationMemberArray>
	: public TStructOpsTypeTraitsBase2<FAssociationMemberArray>
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};
