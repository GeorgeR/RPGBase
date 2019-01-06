#pragma once

#include "CoreMinimal.h"
#include "ScriptInterface.h"
#include "NoExportTypes.h"
#include "AssociationMember.h"
#include "RPGPlayerInterface.h"

#include "AssociationInvitation.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FAssociationInvitation
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FAssociationMember Inviter;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TScriptInterface<IRPGPlayerInterface> Invitee;

	/* Store as UTC */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FDateTime InviteSent;

	FAssociationInvitation()
		: InviteSent(FDateTime::UtcNow()) { }

	/* Check that the inviter is still a member, and the invitee still exists */
	inline bool IsValid()
	{
		if (!Inviter.IsValid())
			return false;

		if (!Invitee->IsValid())
			return false;
	}

	inline bool HasExpired(FTimespan& ExpirationTime)
	{
		auto Now = FDateTime::UtcNow();
		if (InviteSent + ExpirationTime >= Now)
			return true;

		return false;
	}
};
