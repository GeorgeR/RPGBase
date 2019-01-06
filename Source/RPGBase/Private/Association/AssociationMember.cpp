#include "AssociationMember.h"
#include "RPGPlayerInterface.h"
#include "Association.h"
#include "AssociationMemberArray.h"

void FAssociationMember::PreReplicatedRemove(const FAssociationMemberArray& ArraySerializer) const
{
	//if (ArraySerializer.Owner != nullptr)
	//	ArraySerializer.Owner->OnMemberRemoved(*this);
}

void FAssociationMember::PostReplicatedAdd(const FAssociationMemberArray& ArraySerializer) const
{
	//if (ArraySerializer.Owner != nullptr)
	//	ArraySerializer.Owner->OnMemberAdded(*this);
}

bool FAssociationMember::operator==(const FAssociationMember& Other) const
{
	return Player->GetPlayerId() == Other.Player->GetPlayerId();
}

bool FAssociationMember::operator!=(const FAssociationMember& Other) const
{
	return !(*this == Other);
}

bool FAssociationMember::IsValid()
{
	return Player != nullptr && Player->IsValid();
}
