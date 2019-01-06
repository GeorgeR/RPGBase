// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AbilitySystemComponent.h"

#include "RPGAbilitySystemComponent.generated.h"

class IRPGCharacterInterface;

/**
 * Subclass of ability system component with game-specific data
 * Most games will need to make a game-specific subclass to provide utility functions
 */
UCLASS()
class RPGBASE_API URPGAbilitySystemComponent
	: public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	virtual void AddInitialAbilitiesAndEffects(const TEnumAsByte<ENetRole> NetRole, const TScriptInterface<IRPGCharacterInterface>& Character);
	virtual void RemoveInitialAbilitiesAndEffects(const TEnumAsByte<ENetRole> NetRole, const TScriptInterface<IRPGCharacterInterface>& Character);

	/** Returns a list of currently active ability instances that match the tags */
	virtual void GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<UGameplayAbility*>& ActiveAbilities);

	/** Returns the default level used for ability activations, derived from the character */
	virtual int32 GetDefaultAbilityLevel() const;
};
