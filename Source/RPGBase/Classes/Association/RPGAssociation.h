#pragma once

#include "CoreMinimal.h"
#include "Engine/NetSerialization.h"
#include "RPGAssociationMember.h"
#include "RPGAssociationMemberArray.h"

#include "RPGAssociation.generated.h"

class IRPGPlayerInterface;

UCLASS(BlueprintType, Blueprintable)
class RPGBASE_API URPGAssociation 
	: public UObject
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCreated, URPGAssociation*, Association);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInviteAccepted, const TScriptInterface<IRPGPlayerInterface>&, Player);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMemberAdded, const FRPGAssociationMember&, Member);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMemberRemoved, const FRPGAssociationMember&, Member);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChangedRank, const FRPGAssociationMember&, Member, FString, Rank);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDisbanded);
	
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Replicated, Category = "Association")
	FString Id;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Replicated, Category = "Association")
	FString Name;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Replicated, Category = "Association")
	FString Description;

	/* Rank for new members */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Replicated, Category = "Association")
	FString DefaultRank;

	/* List of the members */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Replicated, Category = "Association")
	FRPGAssociationMemberArray Members;

	/* Stored as the others Association Id */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Replicated, Category = "Association")
	TArray<FString> Alliances;

	URPGAssociation();

protected:
	UPROPERTY(BlueprintAssignable)
	FOnCreated OnCreated;

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
	static URPGAssociation* Create(const TScriptInterface<IRPGPlayerInterface>& Creator, const FString& AssociationName);

	/* Returns false if the Inviter can't invite, or the Invitee is already in an Association. Optional localized message. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Association")
	bool Invite(const FRPGAssociationMember& Inviter, const TScriptInterface<IRPGPlayerInterface>& Invitee);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Association")
	bool AddMember(const TScriptInterface<IRPGPlayerInterface>& Player, const FString& Rank = TEXT(""));

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Association")
	bool RemoveMember(const FRPGAssociationMember& Dismisser, const FRPGAssociationMember& Member);

	/* Returns true if the Members rank was changed, false if the Changer didn't have permission. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Association")
	bool ChangeMemberRank(const FRPGAssociationMember& Changer, FRPGAssociationMember& Member, const FString& NewRank);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Association")
	bool Disband(const FRPGAssociationMember& Disbander);
	
	UFUNCTION(BlueprintCallable, Category = "Association")
	bool IsMember(const TScriptInterface<IRPGPlayerInterface>& Player);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Association")
	bool GetMemberForPlayer(const TScriptInterface<IRPGPlayerInterface>& Player, FRPGAssociationMember& Member);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Association")
	bool GetRankForPlayer(const TScriptInterface<IRPGPlayerInterface>& Player, FString& Rank);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const override;

protected:
	/* Implementations */

	/* Create */
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerCreate(const TScriptInterface<IRPGPlayerInterface>& Creator, const FString& AssociationName);
	virtual bool ServerCreate_Validate(const TScriptInterface<IRPGPlayerInterface>& Creator, const FString& AssociationName) { return true; }
	virtual void ServerCreate_Implementation(const TScriptInterface<IRPGPlayerInterface>& Creator, const FString& AssociationName);

	/* Invite */
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerInvite(const FRPGAssociationMember& Inviter, const TScriptInterface<IRPGPlayerInterface>& Invitee);
	virtual bool ServerInvite_Validate(const FRPGAssociationMember& Inviter, const TScriptInterface<IRPGPlayerInterface>& Invitee) { return true; }
	virtual void ServerInvite_Implementation(const FRPGAssociationMember& Inviter, const TScriptInterface<IRPGPlayerInterface>& Invitee);

	/* Add */
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerAddMember(const TScriptInterface<IRPGPlayerInterface>& Player, const FString& Rank = TEXT(""));
	virtual bool ServerAddMember_Validate(const TScriptInterface<IRPGPlayerInterface>& Player, const FString& Rank = TEXT("")) { return true; }
	virtual void ServerAddMember_Implementation(const TScriptInterface<IRPGPlayerInterface>& Player, const FString& Rank = TEXT(""));

	/* Remove */
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRemoveMember(const FRPGAssociationMember& Dismisser, const FRPGAssociationMember& Member);
	virtual bool ServerRemoveMember_Validate(const FRPGAssociationMember& Dismisser, const FRPGAssociationMember& Member) { return true; }
	virtual void ServerRemoveMember_Implementation(const FRPGAssociationMember& Dismisser, const FRPGAssociationMember& Member);

	/* Change Rank */
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerChangeMemberRank(const FRPGAssociationMember& Changer, const FRPGAssociationMember& Member, const FString& NewRank);
	virtual bool ServerChangeMemberRank_Validate(const FRPGAssociationMember& Changer, const FRPGAssociationMember& Member, const FString& NewRank) { return true; }
	virtual void ServerChangeMemberRank_Implementation(const FRPGAssociationMember& Changer, const FRPGAssociationMember& Member, const FString& NewRank);
	
	/* Disband */
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDisband(const FRPGAssociationMember& Disbander);
	virtual bool ServerDisband_Validate(const FRPGAssociationMember& Disbander) { return true; }
	virtual void ServerDisband_Implementation(const FRPGAssociationMember& Disbander);

	virtual bool Invite_Implementation(const FRPGAssociationMember& Inviter, const TScriptInterface<IRPGPlayerInterface>& Invitee);
	virtual bool AddMember_Implementation(const TScriptInterface<IRPGPlayerInterface>& Player, const FString& Rank = TEXT(""));
	virtual bool RemoveMember_Implementation(const FRPGAssociationMember& Dismisser, const FRPGAssociationMember& Member);
	virtual bool ChangeMemberRank_Implementation(const FRPGAssociationMember& Changer, FRPGAssociationMember& Member, const FString& NewRank);
	virtual bool Disband_Implementation(const FRPGAssociationMember& Disbander);
};
