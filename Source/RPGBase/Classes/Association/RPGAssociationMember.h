#pragma once

#include "CoreMinimal.h"

#include "RPGAssociationMember.generated.h"

struct FRPGAssociationMemberArray;
class IRPGPlayerInterface;

USTRUCT(BlueprintType, Blueprintable)
struct FRPGAssociationMember
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

	void PreReplicatedRemove(const FRPGAssociationMemberArray& ArraySerializer) const;
	void PostReplicatedAdd(const FRPGAssociationMemberArray& ArraySerializer) const;

	bool operator==(const FRPGAssociationMember& Other) const;
	bool operator!=(const FRPGAssociationMember& Other) const;

	/* Checks if the player itself is still valid */
	bool IsValid();
};
