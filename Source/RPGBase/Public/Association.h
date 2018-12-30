#pragma once

#include "CoreMinimal.h"
#include "Engine/NetSerialization.h"
#include "AssociationProxy.h"

#include "Association.generated.h"

class APlayerState;

USTRUCT(BlueprintType, Blueprintable)
struct FAssociationMember
	: public FFastArraySerializerItem
{
	GENERATED_BODY()

public:
	/* It's recommended you store the members by their FUniqueNetId */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FString PlayerId;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FString Rank;

	/* Stored as UTC */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FDateTime MemberSince;

	void PreReplicatedRemove(const struct FAssociationMemberArray& InArraySerializer) const;
	void PostReplicatedAdd(const struct FAssociationMemberArray& InArraySerializer) const;
};

USTRUCT(BlueprintType)
struct RPGBASE_API FAssociationMemberArray
	: public FFastArraySerializer
{
	GENERATED_BODY()

public:
	class UAssociation* Owner;

	void RegisterWithOwner(class UAssociation* InOwner);

	/* Access this as though it were the array itself */
	operator TArray<FAssociationMember>&() { return Items; }

	bool NetDeltaSerialize(FNetDeltaSerializeInfo & DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FAssociationMember, FAssociationMemberArray>(Items, DeltaParms, *this);
	}
	
private:
	friend struct FAssociationMember;

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

UCLASS(BlueprintType, Blueprintable)
class RPGBASE_API UAssociation 
	: public UAssociationProxy
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInviteAccepted, APlayerState*, Player);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMemberAdded, FAssociationMember, Member);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMemberRemoved, FAssociationMember, Member);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChangedRank, FAssociationMember, Member, FName, Rank);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDisbanded);
	
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
	FAssociationMemberArray Members;

	/* Stored as the others Association Id */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<int32> Alliances;

	UAssociation();
	
	UPROPERTY(BlueprintAssignable)
	FOnInviteAccepted OnInviteAccepted;

	UPROPERTY(BlueprintAssignable)
	FOnMemberAdded OnMemberAdded;

	UPROPERTY(BlueprintAssignable)
	FOnMemberRemoved OnMemberRemoved;

	UPROPERTY(BlueprintAssignable)
	FOnChangedRank OnChangedRank;

	UPROPERTY(BlueprintAssignable)
	FOnDisbanded OnDisbanded;

	/* Returns the created Association or nullptr if the Creator is already in an Association, or an Association with that name already exists. Optional localized message. */
	/* It's important to attach this to an object (such as an array of Associations in GameMode ASAP. */
	UFUNCTION(BlueprintCallable, Category = "Association")
	static UAssociation* Create(FName InAssociationName, APlayerState* InCreator, FName InCreatorRank, FText& OutMessage);

	UFUNCTION(BlueprintCallable, Category = "Association", meta = (DisplayName = "Create"))
	static void Create_MP(UAssociationProxy* InAccessor, FName InAssociationName, APlayerState* InCreator, FName InCreatorRank);

	/* Returns false if the Inviter can't invite, or the Invitee is already in an Association. Optional localized message. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Association")
	bool Invite(APlayerState* InInviter, APlayerState* InInvitee, FText& OutMessage);
	virtual bool Invite_Implementation(APlayerState* InInviter, APlayerState* InInvitee, FText& OutMessage);

	UFUNCTION(BlueprintCallable, Category = "Association", meta = (DisplayName = "Invite"))
	void Invite_MP(UAssociationProxy* InAccessor, APlayerState* InInviter, APlayerState* InInvitee);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Association")
	bool AddMember(APlayerState* InPlayer, FName InRank = TEXT(""));
	virtual bool AddMember_Implementation(APlayerState* InPlayer, FName InRank = TEXT(""));

	UFUNCTION(BlueprintCallable, Category = "Association", meta = (DisplayName = "AddMember"))
	void AddMember_MP(UAssociationProxy* InAccessor, APlayerState* InPlayer, FName InRank = TEXT(""));

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Association")
	bool RemoveMember(APlayerState* InDismisser, APlayerState* InMember);
	virtual bool RemoveMember_Implementation(APlayerState* InDismisser, APlayerState* InMember);

	UFUNCTION(BlueprintCallable, Category = "Association", meta = (DisplayName = "RemoveMember"))
	void RemoveMember_MP(UAssociationProxy* InAccessor, APlayerState* InDismisser, APlayerState* InMember);

	/* Returns true if the Members rank was changed, false if the Changer didn't have permission. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Association")
	bool ChangeMemberRank(APlayerState* InChanger, APlayerState* InMember, FName InNewRank);
	virtual bool ChangeMemberRank_Implementation(APlayerState* InChanger, APlayerState* InMember, FName InNewRank);

	UFUNCTION(BlueprintCallable, Category = "Association", meta = (DisplayName = "ChangeMemberRank"))
	void ChangeMemberRank_MP(UAssociationProxy* InAccessor, APlayerState* InChanger, APlayerState* InMember, FName InNewRank);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Association")
	bool Disband(APlayerState* InDisbander);
	virtual bool Disband_Implementation(APlayerState* InDisbander);

	UFUNCTION(BlueprintCallable, Category = "Association", meta = (DisplayName = "Disband"))
	void Disband_MP(UAssociationProxy* InAccessor, APlayerState* InDisbander);

	UFUNCTION(BlueprintCallable, Category = "Association")
	bool IsMember(APlayerState* InPlayer);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Association")
	bool GetMemberForPlayer(APlayerState* InPlayer, FAssociationMember& OutMember);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Association")
	bool GetRankForPlayer(APlayerState* InPlayer, FName& OutRank);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const override;
};
