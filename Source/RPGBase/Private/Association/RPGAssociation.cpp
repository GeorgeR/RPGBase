#include "Association/RPGAssociation.h"

#include "Net/UnrealNetwork.h"

#include "RPGBaseMacros.h"
#include "Association/RPGAssociationMember.h"
#include "Association/RPGAssociationMemberArray.h"

URPGAssociation::URPGAssociation()
{
	Members.RegisterWithOwner(this);
}

/* Create */
URPGAssociation* URPGAssociation::Create(const TScriptInterface<IRPGPlayerInterface>& Creator, const FString& AssociationName)
{
	// TODO: Check if on client, server (or single player)
	if (IS_SERVER_OR_SINGLEPLAYER)
	{
		// TODO: Check if Creator is already in association
		auto Result = NewObject<URPGAssociation>(nullptr);

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
bool URPGAssociation::Invite_Implementation(const FRPGAssociationMember& Inviter, const TScriptInterface<IRPGPlayerInterface>& Invitee)
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
bool URPGAssociation::AddMember_Implementation(const TScriptInterface<IRPGPlayerInterface>& Player, const FString& Rank)
{
	// TODO: Check if on client, server (or single player)
	if (IS_SERVER_OR_SINGLEPLAYER)
	{
		if (IsMember(Player))
			return false;

		FRPGAssociationMember NewMember;
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
bool URPGAssociation::RemoveMember_Implementation(const FRPGAssociationMember& Dismisser, const FRPGAssociationMember& Member)
{
	// TODO: Check if on client, server (or single player)
	if (IS_SERVER_OR_SINGLEPLAYER)
	{
		TArray<FRPGAssociationMember>& Members_ = Members;
		for (auto& Member_ : Members_)
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
bool URPGAssociation::ChangeMemberRank_Implementation(const FRPGAssociationMember& Changer, FRPGAssociationMember& Member, const FString& NewRank)
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
bool URPGAssociation::Disband_Implementation(const FRPGAssociationMember& Disbander)
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

bool URPGAssociation::IsMember(const TScriptInterface<IRPGPlayerInterface>& Player)
{
	FRPGAssociationMember Member;
	return GetMemberForPlayer(Player, Member);
}

bool URPGAssociation::GetMemberForPlayer(const TScriptInterface<IRPGPlayerInterface>& Player, FRPGAssociationMember& Member)
{
	TArray<FRPGAssociationMember>& Members_ = Members;
	for (auto& Member_ : Members_)
		if (Member_.Player == Player)
		{
			Member = Member_;
			return true;
		}

	return false;
}

bool URPGAssociation::GetRankForPlayer(const TScriptInterface<IRPGPlayerInterface>& Player, FString& Rank)
{
	FRPGAssociationMember Member;
	if (GetMemberForPlayer(Player, Member))
	{
		Rank = Member.Rank;
		return true;
	}

	return false;
}

void URPGAssociation::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(URPGAssociation, Id, COND_InitialOnly);
	DOREPLIFETIME(URPGAssociation, Name);
	DOREPLIFETIME(URPGAssociation, Description);
	DOREPLIFETIME(URPGAssociation, DefaultRank);
	DOREPLIFETIME(URPGAssociation, Members);
	DOREPLIFETIME(URPGAssociation, Alliances);
}
