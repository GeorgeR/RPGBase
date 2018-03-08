#include "Association.h"
#include "Net/UnrealNetwork.h"

void FAssociationMember::PreReplicatedRemove(const struct FAssociationMemberArray& InArraySerializer) const
{
	if (InArraySerializer.Owner != nullptr)
		InArraySerializer.Owner->OnMemberRemoved.Broadcast(*this);
}

void FAssociationMember::PostReplicatedAdd(const struct FAssociationMemberArray& InArraySerializer) const
{
	if (InArraySerializer.Owner != nullptr)
		InArraySerializer.Owner->OnMemberAdded.Broadcast(*this);
}

void FAssociationMemberArray::RegisterWithOwner(class UAssociation* InOwner)
{
	Owner = InOwner;
}

UAssociation::UAssociation()
{
	// TODO: OnInviteAccepted.

	Members.RegisterWithOwner(this);
}

UAssociation* UAssociation::Create(const FName InAssociationName, APlayerState* InCreator, const FName InCreatorRank, FText& OutMessage)
{
	// TODO: Check if Creator is already in association
	auto Result = NewObject<UAssociation>(nullptr);
	
	Result->Name = InAssociationName;
	Result->AddMember(InCreator, InCreatorRank);

	return Result;
}

void UAssociation::Create_MP(UAssociationAccessor* InAccessor, const FName InAssociationName, APlayerState* InCreator, const FName InCreatorRank)
{
	InAccessor->Server_Create(InAssociationName, InCreator, InCreatorRank);
}

bool UAssociation::Invite_Implementation(APlayerState* InInviter, APlayerState* InInvitee, FText& OutMessage)
{
	// If InInvite is already in an association, return false

	return true;
}

void UAssociation::Invite_MP(UAssociationAccessor* InAccessor, APlayerState* InInviter, APlayerState* InInvitee)
{
	InAccessor->Server_Invite(this, InInviter, InInvitee);
}

bool UAssociation::AddMember_Implementation(APlayerState* InPlayer, const FName InRank /*= TEXT("")*/)
{
	if (IsMember(InPlayer))
		return false;

	FAssociationMember NewMember;
	NewMember.PlayerId = FName(*InPlayer->UniqueId->ToString());
	NewMember.Rank = InRank;
	NewMember.MemberSince = FDateTime::UtcNow();

	TArray<FAssociationMember>& Members = this->Members;
	Members.Add(NewMember);

	return true;
}

void UAssociation::AddMember_MP(UAssociationAccessor* InAccessor, APlayerState* InPlayer, const FName InRank /*= TEXT("")*/)
{
	InAccessor->Server_AddMember(this, InPlayer, InRank);
}

// Default implementation doesn't care who the Dismisser is, you should definitely override this
bool UAssociation::RemoveMember_Implementation(APlayerState* InDismisser, APlayerState* InMember)
{
	TArray<FAssociationMember>& Members = this->Members;
	for (auto i = 0; i < Members.Num(); i++)
	{
		if (Members[i].PlayerId == FName(*InMember->UniqueId->ToString()))
		{
			Members.RemoveAt(i);
			return true;
		}
	}

	return false;
}

void UAssociation::RemoveMember_MP(UAssociationAccessor* InAccessor, APlayerState* InDismisser, APlayerState* InMember)
{
	InAccessor->Server_RemoveMember(this, InDismisser, InMember);
}

bool UAssociation::ChangeMemberRank_Implementation(APlayerState* InChanger, APlayerState* InMember, const FName InNewRank)
{
	FAssociationMember Member;
	if (!GetMemberForPlayer(InMember, Member))
		return false;

	Member.Rank = InNewRank;

	OnChangedRank.Broadcast(Member, InNewRank);

	return true;
}

void UAssociation::ChangeMemberRank_MP(UAssociationAccessor* InAccessor, APlayerState* InChanger, APlayerState* InMember, const FName InNewRank)
{
	InAccessor->Server_ChangeMemberRank(this, InChanger, InMember, InNewRank);
}

bool UAssociation::Disband_Implementation(APlayerState* InDisbander)
{
	if(!IsMember(InDisbander))
		return false;

	OnDisbanded.Broadcast();
	// TODO: Destroy
	return true;
}

void UAssociation::Disband_MP(UAssociationAccessor* InAccessor, APlayerState* InDisbander)
{
	return InAccessor->Server_Disband(this, InDisbander);
}

bool UAssociation::IsMember(APlayerState* InPlayer)
{
	FAssociationMember Member;
	return GetMemberForPlayer(InPlayer, Member);
}

bool UAssociation::GetMemberForPlayer(APlayerState* InPlayer, FAssociationMember& OutMember)
{
	TArray<FAssociationMember>& Members = this->Members;
	for (auto& Member : Members)
		if (Member.PlayerId == FName(*InPlayer->UniqueId->ToString()))
		{
			OutMember = Member;
			return true;
		}

	return false;
}

bool UAssociation::GetRankForPlayer(APlayerState* InPlayer, FName& OutRank)
{
	FAssociationMember Member;
	if (GetMemberForPlayer(InPlayer, Member))
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