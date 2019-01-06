#include "AssociationMemberArray.h"
#include "AssociationMember.h"
#include "Association.h"

FAssociationMemberArray::FAssociationMemberArray()
	: Owner(nullptr) { }

void FAssociationMemberArray::RegisterWithOwner(UAssociation* Owner)
{
	this->Owner = Owner;
}

bool FAssociationMemberArray::NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
{
	return FFastArraySerializer::FastArrayDeltaSerialize<FAssociationMember, FAssociationMemberArray>(Items, DeltaParms, *this);
}
