#pragma once

#include "CoreMinimal.h"
#include "Interface.h"

#include "PlayerInterface.generated.h"

UINTERFACE(MinimalAPI)
class URPGPlayerInterface 
	: public UInterface
{
	GENERATED_BODY()
};

/* In multiplayer this should be implemented by your PlayerState. */
/* This defines the MINIMUM required functionality for the system to work. You should extend it with your specific requirements. */
class RPGBASE_API IRPGPlayerInterface
{
	GENERATED_BODY()

public:
	/* In multiplayer games this should be the FUniqueNetIdRepl.ToString() */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Player")
	FString GetPlayerId() const;
	virtual FString GetPlayerId_Implementation() const = 0;

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Player")
	//FName GetPlayerName() const;
	//virtual FName GetPlayerName_Implementation() const { return NAME_None; }
};
