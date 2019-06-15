#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "RPGItemInstance.h"

#include "RPGItemInstanceFunctionLibrary.generated.h"

class UInterface;
class UTexture2D;

class URPGItem;

UCLASS()
class RPGBASE_API URPGItemInstanceFunctionLibrary
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
#pragma region Accessors
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Item")
	static const FString& GetName(const FRPGItemInstance& ItemInstance);

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Item")
	static const FText& GetDisplayName(const FRPGItemInstance& ItemInstance);

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Item")
	static const FText& GetDescription(const FRPGItemInstance& ItemInstance);

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Item")
	static UTexture2D* GetIcon(const FRPGItemInstance& ItemInstance);

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Item")
	static bool GetIsStackable(const FRPGItemInstance& ItemInstance);

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Item")
	static int32 GetMaxStackSize(const FRPGItemInstance& ItemInstance);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Base|Item")
	static bool ImplementsInterface(const FRPGItemInstance& ItemInstance, TSubclassOf<UInterface> Interface);
#pragma endregion Accessors

#pragma region Functions
	/* Returns the amount actually added to the stack (ie. if it was beyond capacity). You might customize this to add another item with the remaining amount. */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Item")
	static int32 AddToStack(FRPGItemInstance& ItemInstance, int32 Amount);

	/* Returns amount actually removed. */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Item")
	static int32 RemoveFromStack(FRPGItemInstance& ItemInstance, int32 Amount);

	/* Returns the balance */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Item")
	static FRPGItemInstance SplitStack(FRPGItemInstance& ItemInstance, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Item")
	static FRPGItemInstance Clone(FRPGItemInstance& ItemInstance, int32 StackSize);

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Item")
	static URPGItem* GetItem(const FRPGItemInstance& ItemInstance);
#pragma endregion Functions
};
