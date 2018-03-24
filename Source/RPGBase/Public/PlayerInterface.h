#pragma once

#include "CoreMinimal.h"
#include "Interface.h"

#include "PlayerInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPlayerInterface 
	: public UInterface
{
	GENERATED_BODY()
};

/* In multiplayer this should be implemented by your PlayerState. */
class RPGBASE_API IPlayerInterface
{
	GENERATED_BODY()

public:
	/* In multiplayer games this should be the FUniqueNetIdRepl.ToString() */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Player")
	FName GetPlayerId() const;
	virtual FName GetPlayerId_Implementation() const { return NAME_None; }

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Player")
	//FName GetPlayerName() const;
	//virtual FName GetPlayerName_Implementation() const { return NAME_None; }
};