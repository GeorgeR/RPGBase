#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "RPGPlayerInterface.generated.h"

UINTERFACE(MinimalAPI)
class URPGPlayerInterface
	: public UInterface
{
	GENERATED_BODY()
};

/* Used by the Ability system, should be implemented by player and NPC characters. */
class RPGBASE_API IRPGPlayerInterface
{
	GENERATED_BODY()

public:
	/* In multiplayer games this should be the FUniqueNetIdRepl.ToString() */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Player")
	FString GetPlayerId() const;
	virtual FString GetPlayerId_Implementation() const = 0;

	/* Used to check if the player exists (at all, not just if they're online or not) */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Player")
	bool IsValid() const;
	virtual bool IsValid_Implementation() const = 0;
};
