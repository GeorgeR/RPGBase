#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "RPGUserInterface.generated.h"

UENUM(BlueprintType)
enum class ERPGUserType : uint8
{
	OT_None = 0			UMETA(DisplayName = "None"),
	OT_WorldPublic = 1	UMETA(DisplayName = "World (Public)"),
	OT_WorldPrivate = 2	UMETA(DisplayName = "World (Private)"),
	OT_Player = 3		UMETA(DisplayName = "Player"),
	OT_Association = 4	UMETA(DisplayName = "Association")
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URPGUserInterface
	: public UInterface
{
	GENERATED_BODY()
};

/* A user implementable abstraction of an in-game "user" (client, player, etc.) */
class RPGBASE_API IRPGUserInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Player")
	ERPGUserType GetUserType() const;
	virtual ERPGUserType GetUserType_Implementation() const = 0;

	/* In multiplayer games this could be FUniqueNetIdRepl.ToString() for players */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Player")
	FString GetUserId() const;
	virtual FString GetUserId_Implementation() const = 0;
};
