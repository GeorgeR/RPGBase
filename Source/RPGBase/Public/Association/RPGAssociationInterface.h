#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ScriptInterface.h"

#include "RPGAssociationInterface.generated.h"

class IRPGCharacterInterface;

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class URPGAssociationInterface
	: public UInterface
{
	GENERATED_BODY()
};

class RPGBASE_API IRPGAssociationInterface
{
	GENERATED_BODY()

public:
	/* Returns false if the Inviter can't invite, or the Invitee is already in an Association. Optional localized message. */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Association")
	virtual bool Invite(TScriptInterface<IRPGCharacterInterface>& Inviter, TScriptInterface<IRPGCharacterInterface>& Invitee) = 0;

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Association")
	virtual bool AddMember(TScriptInterface<IRPGCharacterInterface>& Player, FString Rank = TEXT("")) = 0;

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Association")
	virtual bool RemoveMember(TScriptInterface<IRPGCharacterInterface>& Dismisser, TScriptInterface<IRPGCharacterInterface>& Member) = 0;

	/* Returns true if the Members rank was changed, false if the Changer didn't have permission. */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Association")
	virtual bool ChangeMemberRank(TScriptInterface<IRPGCharacterInterface>& Changer, TScriptInterface<IRPGCharacterInterface>& Member, FString NewRank) = 0;

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Association")
	virtual bool Disband(TScriptInterface<IRPGCharacterInterface>& Disbander) = 0;
};
