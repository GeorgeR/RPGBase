#include "Association.h"
#include "Net/UnrealNetwork.h"

UAssociation* UAssociation::Create(FName InAssociationName, FName InCreatorPlayerId, FName InCreatorRank, FText& OutMessage)
{
	// TODO: Check if Creator is already in association

	UAssociation* Result = NewObject<UAssociation>(nullptr);
	
	Result->Name = InAssociationName;
	Result->AddMember(InCreatorPlayerId, InCreatorRank);
	
	return Result;
}

void UAssociation::OnInviteAccepted_Implementation(FName InInviteeId)
{
	AddMember(InInviteeId, DefaultRank);
}

bool UAssociation::AddMember_Implementation(FName InPlayerId, FName InRank /*= TEXT("")*/)
{
	if (IsMember(InPlayerId))
		return false;

	FAssociationMember NewMember;
	NewMember.PlayerId = InPlayerId;
	NewMember.Rank = InPlayerId;
	NewMember.MemberSince = FDateTime::UtcNow();

	Members.Add(NewMember);
	return true;
}

// Default implementation doesn't care who the Dismisser is, you should definately override this
bool UAssociation::RemoveMember_Implementation(FName InDismisserId, FName InMemberId)
{
	for (auto i = 0; i < Members.Num(); i++)
	{
		if (Members[i].PlayerId == InMemberId)
		{
			Members.RemoveAt(i);
			return true;
		}
	}

	return false;
}

bool UAssociation::ChangeMemberRank_Implementation(FName InChangerId, FName InMemberId, FName InNewRank)
{
	FAssociationMember Member;
	if (!GetMemberForPlayer(InMemberId, Member))
		return false;

	Member.Rank = InNewRank;
	return true;
}

bool UAssociation::Disband_Implementation(FName InDisbanderId)
{
	if(!IsMember(InDisbanderId))
		return false;

	// TODO: Destroy
	return true;
}

bool UAssociation::IsMember(FName InPlayerId) const
{
	FAssociationMember Member;
	return GetMemberForPlayer(InPlayerId, Member);
}

bool UAssociation::GetMemberForPlayer(FName InPlayerId, FAssociationMember& OutMember) const
{
	for (auto& Member : Members)
		if (Member.PlayerId == InPlayerId)
		{
			OutMember = Member;
			return true;
		}

	return false;
}

bool UAssociation::GetRankForPlayer(FName InPlayerId, FName& OutRank) const
{
	FAssociationMember Member;
	if (GetMemberForPlayer(InPlayerId, Member))
	{
		OutRank = Member.Rank;
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
}