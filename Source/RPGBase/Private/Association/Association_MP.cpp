#include "Association.h"
#include "ScriptInterface.h"

/* Create */
void UAssociation::Server_Create_Implementation(const TScriptInterface<IRPGPlayerInterface>& Creator, const FString& AssociationName)
{
	const auto NewAssociation = UAssociation::Create(Creator, AssociationName);
	if (NewAssociation != nullptr)
		OnCreated.Broadcast(NewAssociation);
}

/* Invite */
void UAssociation::Server_Invite_Implementation(const FAssociationMember& Inviter, const TScriptInterface<IRPGPlayerInterface>& Invitee)
{
	Invite(Inviter, Invitee);
}

/* Add */
void UAssociation::Server_AddMember_Implementation(const TScriptInterface<IRPGPlayerInterface>& Player, const FString& Rank /*= TEXT("")*/)
{

}

/* Remove */
void UAssociation::Server_RemoveMember_Implementation(const FAssociationMember& Dismisser, const FAssociationMember& Member)
{

}

/* Change Rank */
void UAssociation::Server_ChangeMemberRank_Implementation(const FAssociationMember& Changer, const FAssociationMember& Member, const FString& NewRank)
{

}

/* Disband */
void UAssociation::Server_Disband_Implementation(const FAssociationMember& Disbander)
{

}
