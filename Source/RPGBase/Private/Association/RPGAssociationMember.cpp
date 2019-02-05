#include "RPGAssociationMember.h"

#include "RPGPlayerInterface.h"
#include "RPGAssociation.h"
#include "RPGAssociationMemberArray.h"

void FRPGAssociationMember::PreReplicatedRemove(const FRPGAssociationMemberArray& ArraySerializer) const
{
	//if (ArraySerializer.Owner != nullptr)
	//	ArraySerializer.Owner->OnMemberRemoved(*this);
}

void FRPGAssociationMember::PostReplicatedAdd(const FRPGAssociationMemberArray& ArraySerializer) const
{
	//if (ArraySerializer.Owner != nullptr)
	//	ArraySerializer.Owner->OnMemberAdded(*this);
}

bool FRPGAssociationMember::operator==(const FRPGAssociationMember& Other) const
{
	return Player->GetPlayerId() == Other.Player->GetPlayerId();
}

bool FRPGAssociationMember::operator!=(const FRPGAssociationMember& Other) const
{
	return !(*this == Other);
}

bool FRPGAssociationMember::IsValid()
{
	return Player != nullptr && Player->IsValid();
}
