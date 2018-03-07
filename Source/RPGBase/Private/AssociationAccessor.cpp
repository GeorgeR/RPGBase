#include "AssociationAccessor.h"
#include "Association.h"

bool UAssociationAccessor::Server_Create_Validate(FName InAssociationName, APlayerState* InCreator, FName InCreatorRank) {	return true; }
void UAssociationAccessor::Server_Create_Implementation(FName InAssociationName, APlayerState* InCreator, FName InCreatorRank) 
{ 
	FText Message;
	UAssociation* NewAssociation = UAssociation::Create(InAssociationName, InCreator, InCreatorRank, Message);
	if (NewAssociation != nullptr)
		OnCreated.Broadcast(NewAssociation, Message);
}

bool UAssociationAccessor::Server_Invite_Validate(UAssociation* InContext, APlayerState* InInviter, APlayerState* InInvitee) { return true; }
void UAssociationAccessor::Server_Invite_Implementation(UAssociation* InContext, APlayerState* InInviter, APlayerState* InInvitee) 
{ 
	FText Message;
	InContext->Invite(InInviter, InInvitee, Message);
}

bool UAssociationAccessor::Server_AddMember_Validate(UAssociation* InContext, APlayerState* InPlayer, FName InRank /*= TEXT("")*/) { return true; }
void UAssociationAccessor::Server_AddMember_Implementation(UAssociation* InContext, APlayerState* InPlayer, FName InRank /*= TEXT("")*/) { InContext->AddMember(InPlayer, InRank); }

bool UAssociationAccessor::Server_RemoveMember_Validate(UAssociation* InContext, APlayerState* InDismisser, APlayerState* InMember) { return true; }
void UAssociationAccessor::Server_RemoveMember_Implementation(UAssociation* InContext, APlayerState* InDismisser, APlayerState* InMember) { InContext->RemoveMember(InDismisser, InMember); }

bool UAssociationAccessor::Server_ChangeMemberRank_Validate(UAssociation* InContext, APlayerState* InChanger, APlayerState* InMember, FName InNewRank) { return true; }
void UAssociationAccessor::Server_ChangeMemberRank_Implementation(UAssociation* InContext, APlayerState* InChanger, APlayerState* InMember, FName InNewRank) { InContext->ChangeMemberRank(InChanger, InMember, InNewRank); }

bool UAssociationAccessor::Server_Disband_Validate(UAssociation* InContext, APlayerState* InDisbander) { return true; }
void UAssociationAccessor::Server_Disband_Implementation(UAssociation* InContext, APlayerState* InDisbander) { InContext->Disband(InDisbander); }