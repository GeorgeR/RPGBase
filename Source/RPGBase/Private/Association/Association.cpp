#include "Association.h"
#include "RPGBaseMacros.h"
#include "AssociationMember.h"
#include "AssociationMemberArray.h"
#include "Net/UnrealNetwork.h"

UAssociation::UAssociation()
{
	Members.RegisterWithOwner(this);
}

/* Create */
UAssociation* UAssociation::Create(const TScriptInterface<IRPGPlayerInterface>& Creator, const FString& AssociationName)
{
	// TODO: Check if on client, server (or single player)
	if (IS_SERVER_OR_SINGLEPLAYER)
	{
		// TODO: Check if Creator is already in association
		auto Result = NewObject<UAssociation>(nullptr);

		Result->Name = AssociationName;
		// TODO: Add default owner rank
		Result->AddMember(Creator, TEXT("Owner"));

		return Result;
	}
#if WITH_NETWORKING
	else
	{
		// TODO: This static business is no good
		//Server_Create(Creator, AssociationName);
		return nullptr;
	}
#endif
}

/* Invite */
bool UAssociation::Invite_Implementation(const FAssociationMember& Inviter, const TScriptInterface<IRPGPlayerInterface>& Invitee)
{
	// TODO: Check if on client, server (or single player)
	if (IS_SERVER_OR_SINGLEPLAYER)
	{
		// If InInvite is already in an association, return false

		// TODO: Split invite and invite acceptance?

		OnInviteAccepted.Broadcast(Invitee);

		return true;
	}
#if WITH_NETWORKING
	else
	{
		Server_Invite(Inviter, Invitee);
		return true;
	}
#endif
}

/* Add */
bool UAssociation::AddMember_Implementation(const TScriptInterface<IRPGPlayerInterface>& Player, const FString& Rank)
{
	// TODO: Check if on client, server (or single player)
	if (IS_SERVER_OR_SINGLEPLAYER)
	{
		if (IsMember(Player))
			return false;

		FAssociationMember NewMember;
		NewMember.Player = Player;
		NewMember.Rank = Rank == TEXT("") ? DefaultRank : Rank;
		NewMember.MemberSince = FDateTime::UtcNow();

		Members.Add(NewMember);

		//OnMemberAdded.Broadcast()

		return true;
	}
#if WITH_NETWORKING
	else
	{
		Server_AddMember(Player, Rank);
		return true;
	}
#endif
}

/* Remove */
// Default implementation doesn't care who the Dismisser is, you should definitely override this
bool UAssociation::RemoveMember_Implementation(const FAssociationMember& Dismisser, const FAssociationMember& Member)
{
	// TODO: Check if on client, server (or single player)
	if (IS_SERVER_OR_SINGLEPLAYER)
	{
		for (auto& Member_ : Members)
		{
			if (Member_.Player == Member.Player)
			{
				Members.Remove(Member_);
				return true;
			}
		}

		return false;
	}
#if WITH_NETWORKING
	else
	{
		Server_RemoveMember(Dismisser, Member);
		return true;
	}
#endif
}

/* Change Rank */
bool UAssociation::ChangeMemberRank_Implementation(const FAssociationMember& Changer, FAssociationMember& Member, const FString& NewRank)
{
	// TODO: Check if on client, server (or single player)
	if (IS_SERVER_OR_SINGLEPLAYER)
	{
		// TODO: Check that the Changer can actually change the members rank
		Member.Rank = NewRank;
		OnChangedRank.Broadcast(Member, NewRank);

		return true;
	}
#if WITH_NETWORKING
	else
	{
		Server_ChangeMemberRank(Changer, Member, NewRank);
		return true;
	}
#endif
}

/* Disband */
bool UAssociation::Disband_Implementation(const FAssociationMember& Disbander)
{
	// TODO: Check if on client, server (or single player)
	if (IS_SERVER_OR_SINGLEPLAYER)
	{
		// TODO: Check that the disbander can actually disband
		OnDisbanded.Broadcast();
		// TODO: Destroy
		return true;
	}
#if WITH_NETWORKING
	else
	{
		Server_Disband(Disbander);
		return true;
	}
#endif
}

bool UAssociation::IsMember(const TScriptInterface<IRPGPlayerInterface>& Player)
{
	FAssociationMember Member;
	return GetMemberForPlayer(Player, Member);
}

bool UAssociation::GetMemberForPlayer(const TScriptInterface<IRPGPlayerInterface>& Player, FAssociationMember& Member)
{
	for (auto& Member_ : Members)
		if (Member_.Player == Player)
		{
			Member = Member_;
			return true;
		}

	return false;
}

bool UAssociation::GetRankForPlayer(const TScriptInterface<IRPGPlayerInterface>& Player, FString& Rank)
{
	FAssociationMember Member;
	if (GetMemberForPlayer(Player, Member))
	{
		Rank = Member.Rank;
		return true;
	}

	return false;
}

void UAssociation::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UAssociation, Id, COND_InitialOnly);
	DOREPLIFETIME(UAssociation, Name);
	DOREPLIFETIME(UAssociation, Description);
	DOREPLIFETIME(UAssociation, DefaultRank);
	DOREPLIFETIME(UAssociation, Members);
	DOREPLIFETIME(UAssociation, Alliances);
}
