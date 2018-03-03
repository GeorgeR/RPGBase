#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Association.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FAssociationMember
{
	GENERATED_BODY()

public:
	/* It's recommended you store the members by their FUniqueNetId */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FName PlayerId;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FName Rank;

	/* Stored as UTC */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FDateTime MemberSince;
};

UCLASS(BlueprintType, Blueprintable)
class RPGBASE_API UAssociation 
	: public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Replicated)
	int32 Id;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Replicated)
	FName Name;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Replicated)
	FName Description;

	/* Rank for new members */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Replicated)
	FName DefaultRank;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<FAssociationMember> Members;

	/* Stored as the others Association Id */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<int32> Alliances;

	/* Returns the created Association or nullptr if the Creator is already in an Association, or an Association with that name already exists. Optional localized message. */
	/* It's important to attach this to an object (such as an array of Associations in GameMode ASAP. */
	UFUNCTION(BlueprintCallable, Category = "Association")
	static UAssociation* Create(FName InAssociationName, FName InCreatorPlayerId, FName InCreatorRank, FText& OutMessage);

	/* Returns false if the Inviter can't invite, or the Invitee is already in an Association. Optional localized message. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Association")
	bool Invite(FName InInviterId, FName InInviteeId, FText& OutMessage);
	virtual bool Invite_Implementation(FName InInviterId, FName InInviteeId, FText& OutMessage) { return false; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Association")
	void OnInviteAccepted(FName InInviteeId);
	virtual void OnInviteAccepted_Implementation(FName InInviteeId);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Association")
	bool AddMember(FName InPlayerId, FName InRank = TEXT(""));
	virtual bool AddMember_Implementation(FName InPlayerId, FName InRank = TEXT(""));

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Association")
	bool RemoveMember(FName InDismisserId, FName InMemberId);
	virtual bool RemoveMember_Implementation(FName InDismisserId, FName InMemberId);

	/* Returns true if the Members rank was changed, false if the Changer didn't have permission. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Association")
	bool ChangeMemberRank(FName InChangerId, FName InMemberId, FName InNewRank);
	virtual bool ChangeMemberRank_Implementation(FName InChangerId, FName InMemberId, FName InNewRank);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Association")
	bool Disband(FName InDisbanderId);
	virtual bool Disband_Implementation(FName InDisbanderId);

	UFUNCTION(BlueprintCallable, Category = "Association")
	bool IsMember(FName InPlayerId) const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Association")
	bool GetMemberForPlayer(FName InPlayerId, FAssociationMember& OutMember) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Association")
	bool GetRankForPlayer(FName InPlayerId, FName& OutRank) const;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const override;
};