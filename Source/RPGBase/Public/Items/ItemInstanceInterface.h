#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "ItemInstanceInterface.generated.h"

class UItem;

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UItemInstanceInterface
	: public UInterface
{
	GENERATED_BODY()
};

class RPGBASE_API IItemInstanceInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Item")
	virtual void Create(const TSoftClassPtr<UItem>& ItemClass, const FString& Id) = 0;

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Item")
	virtual UItem* GetItem() = 0;

	/* Add the specified amount to the stack. If this goes above the max stack size, the remainder is returned */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Item")
	virtual int32 AddToStack(int32 Count) = 0;

	/* Removes the specified amount from the stack, returns the actual amount removed (if the requested amount is beyond what's available) */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Item")
	virtual int32 RemoveFromStack(int32 Count) = 0;
};
