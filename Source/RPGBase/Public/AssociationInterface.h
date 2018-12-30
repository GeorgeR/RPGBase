#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ScriptInterface.h"

#include "AssociationInterface.generated.h"

class IRPGPlayerInterface;

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UAssociationInterface
	: public UInterface
{
	GENERATED_BODY()
};

class RPGBASE_API IAssociationInterface
{
	GENERATED_BODY()

public:
	/* Returns false if the Inviter can't invite, or the Invitee is already in an Association. Optional localized message. */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Association")
	virtual bool Invite(TScriptInterface<IRPGPlayerInterface>& Inviter, TScriptInterface<IRPGPlayerInterface>& Invitee) = 0;

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Association")
	virtual bool AddMember(TScriptInterface<IRPGPlayerInterface>& Player, FString Rank = TEXT("")) = 0;

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Association")
	virtual bool RemoveMember(TScriptInterface<IRPGPlayerInterface>& Dismisser, TScriptInterface<IRPGPlayerInterface>& Member) = 0;

	/* Returns true if the Members rank was changed, false if the Changer didn't have permission. */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Association")
	virtual bool ChangeMemberRank(TScriptInterface<IRPGPlayerInterface>& Changer, TScriptInterface<IRPGPlayerInterface>& Member, FString NewRank) = 0;

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Association")
	virtual bool Disband(TScriptInterface<IRPGPlayerInterface>& Disbander) = 0;
};
