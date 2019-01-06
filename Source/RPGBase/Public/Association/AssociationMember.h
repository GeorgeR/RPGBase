#pragma once

#include "CoreMinimal.h"

#include "AssociationMember.generated.h"

struct FAssociationMemberArray;
class IRPGPlayerInterface;

USTRUCT(BlueprintType, Blueprintable)
struct FAssociationMember
	: public FFastArraySerializerItem
{
	GENERATED_BODY()

public:
	/* It's recommended you store the members by their FUniqueNetId */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TScriptInterface<IRPGPlayerInterface> Player;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FString Rank;

	/* Stored as UTC */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FDateTime MemberSince;

	void PreReplicatedRemove(const FAssociationMemberArray& ArraySerializer) const;
	void PostReplicatedAdd(const FAssociationMemberArray& ArraySerializer) const;

	bool operator==(const FAssociationMember& Other) const;
	bool operator!=(const FAssociationMember& Other) const;

	/* Checks if the player itself is still valid */
	bool IsValid();
};
