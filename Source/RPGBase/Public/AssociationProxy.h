#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

#include "AssociationProxy.generated.h"

/* Wrapper to call RPC's for a Container via a PlayerController */
UCLASS(BlueprintType)
class RPGBASE_API UAssociationProxy
	: public UObject 
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCreated, UAssociation*, Association, FText, Message);

public:
	UPROPERTY(BlueprintAssignable)
	FOnCreated OnCreated;

private:
	friend class UAssociation;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Create(FName InAssociationName, APlayerState* InCreator, FName InCreatorRank);
	virtual bool Server_Create_Validate(FName InAssociationName, APlayerState* InCreator, FName InCreatorRank);
	virtual void Server_Create_Implementation(FName InAssociationName, APlayerState* InCreator, FName InCreatorRank);

	// Invite
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Invite(UAssociation* InContext, APlayerState* InInviter, APlayerState* InInvitee);
	virtual bool Server_Invite_Validate(UAssociation* InContext, APlayerState* InInviter, APlayerState* InInvitee);
	virtual void Server_Invite_Implementation(UAssociation* InContext, APlayerState* InInviter, APlayerState* InInvitee);

	// Add
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_AddMember(UAssociation* InContext, APlayerState* InPlayer, FName InRank = TEXT(""));
	virtual bool Server_AddMember_Validate(UAssociation* InContext, APlayerState* InPlayer, FName InRank = TEXT(""));
	virtual void Server_AddMember_Implementation(UAssociation* InContext, APlayerState* InPlayer, FName InRank = TEXT(""));

	// Remove
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_RemoveMember(UAssociation* InContext, APlayerState* InDismisser, APlayerState* InMember);
	virtual bool Server_RemoveMember_Validate(UAssociation* InContext, APlayerState* InDismisser, APlayerState* InMember);
	virtual void Server_RemoveMember_Implementation(UAssociation* InContext, APlayerState* InDismisser, APlayerState* InMember);

	// Change Member Rank
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_ChangeMemberRank(UAssociation* InContext, APlayerState* InChanger, APlayerState* InMember, FName InNewRank);
	virtual bool Server_ChangeMemberRank_Validate(UAssociation* InContext, APlayerState* InChanger, APlayerState* InMember, FName InNewRank);
	virtual void Server_ChangeMemberRank_Implementation(UAssociation* InContext, APlayerState* InChanger, APlayerState* InMember, FName InNewRank);

	// Disband
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Disband(UAssociation* InContext, APlayerState* InDisbander);
	virtual bool Server_Disband_Validate(UAssociation* InContext, APlayerState* InDisbander);
	virtual void Server_Disband_Implementation(UAssociation* InContext, APlayerState* InDisbander);
};