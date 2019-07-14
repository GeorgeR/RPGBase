#pragma once

#include "CoreMinimal.h"
#include "Engine/NetSerialization.h"

#include "RPGAssociationMember.h"

#include "RPGAssociationMemberArray.generated.h"

USTRUCT(BlueprintType)
struct RPGBASE_API FRPGAssociationMemberArray
	: public FFastArraySerializer
{
	GENERATED_BODY()

public:
	FRPGAssociationMemberArray();

	FORCEINLINE int32 Add(FRPGAssociationMember& Item)
	{
		auto Result = Items.Add(Item);
		MarkItemDirty(Item);
		return Result;
	}

	int32 Remove(const FRPGAssociationMember& Item)
	{
		auto Result = Items.Remove(Item);
		MarkArrayDirty();
		return Result;
	}
	
	void RegisterWithOwner(class URPGAssociation* InOwner);

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms);

	template <typename TElementType, typename TSerializerType>
	bool ShouldWriteFastArrayItem(const TElementType& Item, const bool bIsWritingOnClient)
	{
		if (bIsWritingOnClient)
			return Item.ReplicationID != INDEX_NONE;

		return true;
	}

	/* Access this as though it were the array itself */
	operator TArray<FRPGAssociationMember>&() { return Items; }

private:
	friend struct FRPGAssociationMember;

	UPROPERTY()
	URPGAssociation* Owner;

	UPROPERTY()
	TArray<FRPGAssociationMember> Items;
};

template<>
struct TStructOpsTypeTraits<FRPGAssociationMemberArray>
	: public TStructOpsTypeTraitsBase2<FRPGAssociationMemberArray>
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};
