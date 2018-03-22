#include "AssociationProxy.h"
#include "Association.h"

bool UAssociationProxy::Server_Create_Validate(FName InAssociationName, APlayerState* InCreator, FName InCreatorRank) {	return true; }
void UAssociationProxy::Server_Create_Implementation(FName InAssociationName, APlayerState* InCreator, FName InCreatorRank) 
{ 
	FText Message;
	const auto NewAssociation = UAssociation::Create(InAssociationName, InCreator, InCreatorRank, Message);
	if (NewAssociation != nullptr)
		OnCreated.Broadcast(NewAssociation, Message);
}

bool UAssociationProxy::Server_Invite_Validate(UAssociation* InContext, APlayerState* InInviter, APlayerState* InInvitee) { return true; }
void UAssociationProxy::Server_Invite_Implementation(UAssociation* InContext, APlayerState* InInviter, APlayerState* InInvitee) 
{ 
	FText Message;
	InContext->Invite(InInviter, InInvitee, Message);
}

bool UAssociationProxy::Server_AddMember_Validate(UAssociation* InContext, APlayerState* InPlayer, FName InRank /*= TEXT("")*/) { return true; }
void UAssociationProxy::Server_AddMember_Implementation(UAssociation* InContext, APlayerState* InPlayer, FName InRank /*= TEXT("")*/) { InContext->AddMember(InPlayer, InRank); }

bool UAssociationProxy::Server_RemoveMember_Validate(UAssociation* InContext, APlayerState* InDismisser, APlayerState* InMember) { return true; }
void UAssociationProxy::Server_RemoveMember_Implementation(UAssociation* InContext, APlayerState* InDismisser, APlayerState* InMember) { InContext->RemoveMember(InDismisser, InMember); }

bool UAssociationProxy::Server_ChangeMemberRank_Validate(UAssociation* InContext, APlayerState* InChanger, APlayerState* InMember, FName InNewRank) { return true; }
void UAssociationProxy::Server_ChangeMemberRank_Implementation(UAssociation* InContext, APlayerState* InChanger, APlayerState* InMember, FName InNewRank) { InContext->ChangeMemberRank(InChanger, InMember, InNewRank); }

bool UAssociationProxy::Server_Disband_Validate(UAssociation* InContext, APlayerState* InDisbander) { return true; }
void UAssociationProxy::Server_Disband_Implementation(UAssociation* InContext, APlayerState* InDisbander) { InContext->Disband(InDisbander); }