#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemInstance.h"
#include "Engine/Texture2D.h"

#include "Item.generated.h"

/* Base class for an item. Create a child blueprint to create a new item. */
UCLASS(BlueprintType)
class RPGBASE_API UItem 
	: public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName Name;

	/* Localizable name */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText DisplayName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText Description;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UTexture2D* Icon;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bIsStackable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 MaxStackSize;

#pragma region ItemInstance Functions
	/* These are just wrappers, they called the non-BP function on the ItemInstance. */

	/* Returns the amount actually added to the stack (ie. if it was beyond capacity). You might customize this to add another item with the remaining amount. */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Item")
	static int32 AddToStack(FItemInstance& InItemInstance, int32 InAmount) { return InItemInstance.AddToStack(InAmount); }

	/* Returns amount actually removed. */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Item")
	static int32 RemoveFromStack(FItemInstance& InItemInstance, int32 InAmount) { return InItemInstance.RemoveFromStack(InAmount); }

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Item")
	static FItemInstance SplitStack(FItemInstance& InItemInstance, int32 InAmount) { return InItemInstance.SplitStack(InAmount); }

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Item")
	static FItemInstance Clone(FItemInstance& InItemInstance, int32 InStackSize) { return InItemInstance.Clone(InStackSize); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Base|Item")
	static bool IsNullItem(FItemInstance& InItemInstance) { return InItemInstance.IsNullItem(); }
#pragma endregion ItemInstance Functions
};

UCLASS(BlueprintType)
class RPGBASE_API UNullItem
	: public UItem
{
	GENERATED_BODY()

public:
	UNullItem();

	static UNullItem* Get();
	static FItemInstance& GetInstance();
};