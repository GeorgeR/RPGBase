#include "Association/RPGAssociationMemberArray.h"

#include "Association/RPGAssociationMember.h"
#include "Association/RPGAssociation.h"

FRPGAssociationMemberArray::FRPGAssociationMemberArray()
	: Owner(nullptr) { }

void FRPGAssociationMemberArray::RegisterWithOwner(URPGAssociation* InOwner)
{
	this->Owner = InOwner;
}

bool FRPGAssociationMemberArray::NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
{
	return FFastArraySerializer::FastArrayDeltaSerialize<FRPGAssociationMember, FRPGAssociationMemberArray>(Items, DeltaParms, *this);
}
