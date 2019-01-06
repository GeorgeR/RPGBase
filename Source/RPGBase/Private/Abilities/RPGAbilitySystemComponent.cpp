// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "RPGAbilitySystemComponent.h"

#include "AbilitySystemGlobals.h"
#include "RPGCharacterInterface.h"
#include "AbilitySystemComponent.h"

void URPGAbilitySystemComponent::AddInitialAbilitiesAndEffects(const TEnumAsByte<ENetRole> NetRole, const TScriptInterface<IRPGCharacterInterface>& Character)
{
	if (NetRole != ENetRole::ROLE_Authority)
		return;

	TArray<TSoftClassPtr<UGameplayAbility>> Abilities;
	if (IRPGCharacterInterface::Execute_GetInitialAbilities(Character.GetObject(), Abilities))
		for (auto& Ability : Abilities)
			GiveAbility(FGameplayAbilitySpec(Ability.LoadSynchronous(), 1, INDEX_NONE, this));

	TArray<TSoftClassPtr<UGameplayEffect>> Effects;
	if(IRPGCharacterInterface::Execute_GetInitialEffects(Character.GetObject(), Effects))
		for (auto& Effect : Effects)
		{
			auto EffectContext = MakeEffectContext();
			EffectContext.AddSourceObject(Character.GetObject());

			auto EffectHandle = MakeOutgoingSpec(Effect.LoadSynchronous(), 1.0f, EffectContext);
			if (EffectHandle.IsValid())
				auto ActiveHandle = ApplyGameplayEffectSpecToTarget(*EffectHandle.Data.Get(), this);
		}
}

void URPGAbilitySystemComponent::RemoveInitialAbilitiesAndEffects(const TEnumAsByte<ENetRole> NetRole, const TScriptInterface<IRPGCharacterInterface>& Character)
{
	if (NetRole != ENetRole::ROLE_Authority)
		return;

	TArray<TSoftClassPtr<UGameplayAbility>> Abilities;
	if (Character->GetInitialAbilities(Abilities))
	{
		TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
		for (const auto& Spec : GetActivatableAbilities())
			if ((Spec.SourceObject == Character.GetObject()) && Abilities.Contains(Spec.Ability->GetClass()))
				AbilitiesToRemove.Add(Spec.Handle);

		for (auto& Ability : AbilitiesToRemove)
			ClearAbility(Ability);
	}

	FGameplayEffectQuery Query;
	Query.EffectSource = this;
	RemoveActiveEffects(Query);
}

void URPGAbilitySystemComponent::GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<UGameplayAbility*>& ActiveAbilities)
{
	TArray<FGameplayAbilitySpec*> AbilitiesToActivate;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTagContainer, AbilitiesToActivate, false);

	// Iterate the list of all ability specs
	for (auto Spec : AbilitiesToActivate)
	{
		// Iterate all instances on this ability spec
		auto AbilityInstances = Spec->GetAbilityInstances();
		for (auto ActiveAbility : AbilityInstances)
			ActiveAbilities.Add(Cast<UGameplayAbility>(ActiveAbility));
	}
}

int32 URPGAbilitySystemComponent::GetDefaultAbilityLevel() const
{
	auto OwningCharacter = Cast<IRPGCharacterInterface>(OwnerActor);
	if (OwningCharacter)
		OwningCharacter->GetLevel();

	return 1;
}
