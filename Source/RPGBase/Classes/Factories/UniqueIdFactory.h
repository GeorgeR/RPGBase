#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "UniqueIdFactory.generated.h"

UCLASS(BlueprintType, Blueprintable)
class RPGBASE_API UUniqueIdFactory
	: public UObject
{
	GENERATED_BODY()

public:
	/* Return a Unique Id for the given context (ie. ItemInstance, or could be more specific) */
	UFUNCTION(Blueprintcallable, Category = "RPG Base|Utilities")
	virtual FString GetNewId(const FString& Context);
};
