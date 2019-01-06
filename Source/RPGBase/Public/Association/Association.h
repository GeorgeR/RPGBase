#pragma once

#include "CoreMinimal.h"
#include "Engine/NetSerialization.h"
#include "AssociationMember.h"
#include "AssociationMemberArray.h"

#include "Association.generated.h"

class IRPGPlayerInterface;

UCLASS(BlueprintType, Blueprintable)
class RPGBASE_API UAssociation 
	: public UObject
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCreated, UAssociation*, Association);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInviteAccepted, const TScriptInterface<IRPGPlayerInterface>&, Player);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMemberAdded, const FAssociationMember&, Member);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMemberRemoved, const FAssociationMember&, Member);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChangedRank, const FAssociationMember&, Member, FString, Rank);
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
	FAssociationMemberArray Members;

	/* Stored as the others Association Id */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Replicated, Category = "Association")
	TArray<FString> Alliances;

	UAssociation();

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
	static UAssociation* Create(const TScriptInterface<IRPGPlayerInterface>& Creator, const FString& AssociationName);

	/* Returns false if the Inviter can't invite, or the Invitee is already in an Association. Optional localized message. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Association")
	bool Invite(const FAssociationMember& Inviter, const TScriptInterface<IRPGPlayerInterface>& Invitee);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Association")
	bool AddMember(const TScriptInterface<IRPGPlayerInterface>& Player, const FString& Rank = TEXT(""));

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Association")
	bool RemoveMember(const FAssociationMember& Dismisser, const FAssociationMember& Member);

	/* Returns true if the Members rank was changed, false if the Changer didn't have permission. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Association")
	bool ChangeMemberRank(const FAssociationMember& Changer, FAssociationMember& Member, const FString& NewRank);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Association")
	bool Disband(const FAssociationMember& Disbander);
	
	UFUNCTION(BlueprintCallable, Category = "Association")
	bool IsMember(const TScriptInterface<IRPGPlayerInterface>& Player);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Association")
	bool GetMemberForPlayer(const TScriptInterface<IRPGPlayerInterface>& Player, FAssociationMember& Member);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Association")
	bool GetRankForPlayer(const TScriptInterface<IRPGPlayerInterface>& Player, FString& Rank);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const override;

protected:
	/* Implementations */

	/* Create */
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Create(const TScriptInterface<IRPGPlayerInterface>& Creator, const FString& AssociationName);
	virtual bool Server_Create_Validate(const TScriptInterface<IRPGPlayerInterface>& Creator, const FString& AssociationName) { return true; }
	virtual void Server_Create_Implementation(const TScriptInterface<IRPGPlayerInterface>& Creator, const FString& AssociationName);

	/* Invite */
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Invite(const FAssociationMember& Inviter, const TScriptInterface<IRPGPlayerInterface>& Invitee);
	virtual bool Server_Invite_Validate(const FAssociationMember& Inviter, const TScriptInterface<IRPGPlayerInterface>& Invitee) { return true; }
	virtual void Server_Invite_Implementation(const FAssociationMember& Inviter, const TScriptInterface<IRPGPlayerInterface>& Invitee);

	/* Add */
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_AddMember(const TScriptInterface<IRPGPlayerInterface>& Player, const FString& Rank = TEXT(""));
	virtual bool Server_AddMember_Validate(const TScriptInterface<IRPGPlayerInterface>& Player, const FString& Rank = TEXT("")) { return true; }
	virtual void Server_AddMember_Implementation(const TScriptInterface<IRPGPlayerInterface>& Player, const FString& Rank = TEXT(""));

	/* Remove */
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_RemoveMember(const FAssociationMember& Dismisser, const FAssociationMember& Member);
	virtual bool Server_RemoveMember_Validate(const FAssociationMember& Dismisser, const FAssociationMember& Member) { return true; }
	virtual void Server_RemoveMember_Implementation(const FAssociationMember& Dismisser, const FAssociationMember& Member);

	/* Change Rank */
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_ChangeMemberRank(const FAssociationMember& Changer, const FAssociationMember& Member, const FString& NewRank);
	virtual bool Server_ChangeMemberRank_Validate(const FAssociationMember& Changer, const FAssociationMember& Member, const FString& NewRank) { return true; }
	virtual void Server_ChangeMemberRank_Implementation(const FAssociationMember& Changer, const FAssociationMember& Member, const FString& NewRank);
	
	/* Disband */
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Disband(const FAssociationMember& Disbander);
	virtual bool Server_Disband_Validate(const FAssociationMember& Disbander) { return true; }
	virtual void Server_Disband_Implementation(const FAssociationMember& Disbander);

	virtual bool Invite_Implementation(const FAssociationMember& Inviter, const TScriptInterface<IRPGPlayerInterface>& Invitee);
	virtual bool AddMember_Implementation(const TScriptInterface<IRPGPlayerInterface>& Player, const FString& Rank = TEXT(""));
	virtual bool RemoveMember_Implementation(const FAssociationMember& Dismisser, const FAssociationMember& Member);
	virtual bool ChangeMemberRank_Implementation(const FAssociationMember& Changer, FAssociationMember& Member, const FString& NewRank);
	virtual bool Disband_Implementation(const FAssociationMember& Disbander);
};
