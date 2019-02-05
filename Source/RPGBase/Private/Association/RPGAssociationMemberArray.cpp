#include "RPGAssociationMemberArray.h"

#include "RPGAssociationMember.h"
#include "RPGAssociation.h"

FRPGAssociationMemberArray::FRPGAssociationMemberArray()
	: Owner(nullptr) { }

void FRPGAssociationMemberArray::RegisterWithOwner(URPGAssociation* Owner)
{
	this->Owner = Owner;
}

bool FRPGAssociationMemberArray::NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
{
	return FFastArraySerializer::FastArrayDeltaSerialize<FRPGAssociationMember, FRPGAssociationMemberArray>(Items, DeltaParms, *this);
}
