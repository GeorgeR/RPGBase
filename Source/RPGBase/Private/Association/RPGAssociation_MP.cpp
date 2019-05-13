#include "Association/RPGAssociation.h"

#include "ScriptInterface.h"

/* Create */
void URPGAssociation::Server_Create_Implementation(const TScriptInterface<IRPGPlayerInterface>& Creator, const FString& AssociationName)
{
	const auto NewAssociation = URPGAssociation::Create(Creator, AssociationName);
	if (NewAssociation != nullptr)
		OnCreated.Broadcast(NewAssociation);
}

/* Invite */
void URPGAssociation::Server_Invite_Implementation(const FRPGAssociationMember& Inviter, const TScriptInterface<IRPGPlayerInterface>& Invitee)
{
	Invite(Inviter, Invitee);
}

/* Add */
void URPGAssociation::Server_AddMember_Implementation(const TScriptInterface<IRPGPlayerInterface>& Player, const FString& Rank /*= TEXT("")*/)
{

}

/* Remove */
void URPGAssociation::Server_RemoveMember_Implementation(const FRPGAssociationMember& Dismisser, const FRPGAssociationMember& Member)
{

}

/* Change Rank */
void URPGAssociation::Server_ChangeMemberRank_Implementation(const FRPGAssociationMember& Changer, const FRPGAssociationMember& Member, const FString& NewRank)
{

}

/* Disband */
void URPGAssociation::Server_Disband_Implementation(const FRPGAssociationMember& Disbander)
{

}
