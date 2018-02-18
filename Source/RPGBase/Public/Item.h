#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Item.generated.h"

UCLASS(BlueprintType)
class RPGBASE_API UItem 
	: public UObject
{
	GENERATED_BODY()
	
public:
#pragma region Immutable Properties
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName Name;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName Description;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UTexture2D* Icon;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bIsStackable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 MaxStackSize;
#pragma endregion Immutable Properties

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 StackSize;

	/* Returns the amount actually added to the stack (ie. if it was beyond capacity). You might customize this to add another item with the remaining amount. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Item")
	int32 AddToStack(int32 InAmount);

	/* Returns amount actually removed. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Item")
	int32 RemoveFromStack(int32 InAmount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Item")
	UItem* SplitStack(int32 InAmount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Item")
	UItem* Clone(int32 InStackSize);
};

UCLASS(BlueprintType)
class RPGBASE_API UNullItem
	: public UItem
{
	GENERATED_BODY()

public:
	UNullItem();

	static UNullItem* Get();
};