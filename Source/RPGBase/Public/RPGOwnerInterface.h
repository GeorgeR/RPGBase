#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "RPGOwnerInterface.generated.h"

UENUM(BlueprintType)
enum class ERPGOwnerType : uint8
{
	OT_None = 0			UMETA(DisplayName = "None"),
	OT_WorldPublic = 1	UMETA(DisplayName = "World (Public)"),
	OT_WorldPrivate = 2	UMETA(DisplayName = "World (Private)"),
	OT_Player = 3		UMETA(DisplayName = "Player"),
	OT_Association = 4	UMETA(DisplayName = "Association")
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URPGOwnerInterface
	: public UInterface
{
	GENERATED_BODY()
};

/* A user implementable abstraction of an "owner" */
class RPGBASE_API IRPGOwnerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Player")
	ERPGOwnerType GetOwnerType() const;
	virtual ERPGOwnerType GetOwnerType_Implementation() const = 0;

	/* In multiplayer games this could be FUniqueNetIdRepl.ToString() for players */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Player")
	FString GetOwnerId() const;
	virtual FString GetOwnerId_Implementation() const = 0;
};
