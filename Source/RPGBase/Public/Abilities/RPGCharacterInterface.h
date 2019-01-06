#pragma once

#include "CoreMinimal.h"
#include "Interface.h"
#include "PointerIsConvertibleFromTo.h"

#include "RPGCharacterInterface.generated.h"

class UAbilitySystemComponent;

UINTERFACE(MinimalAPI, BlueprintType)
class URPGCharacterInterface
	: public UInterface
{
	GENERATED_BODY()
};

class RPGBASE_API IRPGCharacterInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Character", meta = (DisplayName = "GetAbilitySystemComponent"))
	UAbilitySystemComponent* GetAbilitySystemComponent_BP() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent_BP_Implementation() const = 0;

	template <class TAbilitySystemComponent, class = typename TEnableIf<TPointerIsConvertibleFromTo<TAbilitySystemComponent*, UAbilitySystemComponent>::Value>::Type>
	FORCEINLINE TAbilitySystemComponent* GetAbilitySystemComponent() const
	{
		return Cast<TAbilitySystemComponent>(GetAbilitySystemComponent_BP());
	}

	/* (Optional) gets the initial abilities to grant to this character, return false if there aren't any */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Character")
	bool GetInitialAbilities(TArray<TSoftClassPtr<UGameplayAbility>>& Abilities) const;
	virtual bool GetInitialAbilities_Implementation(TArray<TSoftClassPtr<UGameplayAbility>>& Abilities) const { return false; }

	/* (Optional) gets the initial effects to grant to this character */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Character")
	bool GetInitialEffects(TArray<TSoftClassPtr<UGameplayEffect>>& Effects) const;
	virtual bool GetInitialEffects_Implementation(TArray<TSoftClassPtr<UGameplayEffect>>& Effects) const { return false; }

	/** Returns the character level that is passed to the ability system */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Character")
	int32 GetLevel() const;
	virtual int32 GetLevel_Implementation() const { return 1; }

	/** Modifies the character level, this may change abilities. Returns true on success */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Character")
	bool SetLevel(int32 Level);
	virtual bool SetLevel_Implementation(int32 Level) { return true; }
};
