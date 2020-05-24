#include "Association/RPGAssociation.h"

#include "UObject/ScriptInterface.h"

/* Create */
void URPGAssociation::ServerCreate_Implementation(const TScriptInterface<IRPGPlayerInterface>& Creator, const FString& AssociationName)
{
	const auto NewAssociation = URPGAssociation::Create(Creator, AssociationName);
	if (NewAssociation != nullptr)
		OnCreated.Broadcast(NewAssociation);
}

/* Invite */
void URPGAssociation::ServerInvite_Implementation(const FRPGAssociationMember& Inviter, const TScriptInterface<IRPGPlayerInterface>& Invitee)
{
	Invite(Inviter, Invitee);
}

/* Add */
void URPGAssociation::ServerAddMember_Implementation(const TScriptInterface<IRPGPlayerInterface>& Player, const FString& Rank /*= TEXT("")*/)
{

}

/* Remove */
void URPGAssociation::ServerRemoveMember_Implementation(const FRPGAssociationMember& Dismisser, const FRPGAssociationMember& Member)
{

}

/* Change Rank */
void URPGAssociation::ServerChangeMemberRank_Implementation(const FRPGAssociationMember& Changer, const FRPGAssociationMember& Member, const FString& NewRank)
{

}

/* Disband */
void URPGAssociation::ServerDisband_Implementation(const FRPGAssociationMember& Disbander)
{

}
