#pragma once

#include "CoreMinimal.h"
#include "UObject/ScriptInterface.h"
#include "UObject/NoExportTypes.h"

#include "RPGAssociationMember.h"
#include "Interfaces/RPGPlayerInterface.h"

#include "RPGAssociationInvitation.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FRPGAssociationInvitation
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FRPGAssociationMember Inviter;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TScriptInterface<IRPGPlayerInterface> Invitee;

	/* Store as UTC */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FDateTime InviteSent;

	FRPGAssociationInvitation()
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
