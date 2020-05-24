#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UObject/ScriptInterface.h"
#include "UObject/SoftObjectPtr.h"

#include "Items/RPGItemInstance.h"

#include "RPGContainerInstanceInterface.generated.h"

class URPGContainer;
class IRPGCharacterInterface;
class IRPGUserInterface;

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class URPGContainerInstanceInterface
	: public UInterface
{
	GENERATED_BODY()
};

class RPGBASE_API IRPGContainerInstanceInterface
{
	GENERATED_BODY()

public:
#pragma region Setup
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container")
	virtual void Create(const TSoftClassPtr<URPGContainer>& ContainerClass, const FString& Id, const TScriptInterface<IRPGUserInterface>& Owner) = 0;

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container")
	virtual void SetContainerOwner(TScriptInterface<IRPGUserInterface>& Owner) = 0;
#pragma endregion

#pragma region Queries
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container")
	virtual URPGContainer* GetContainer() = 0;

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container")
	virtual const TScriptInterface<IRPGUserInterface>& GetContainerOwner(TScriptInterface<IRPGUserInterface>& Owner) const = 0;

	/* Returns total capacity of the container (rows * columns) */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container")
	virtual int32 GetCapacity() = 0;

	/* Usually return false if the container is full and you can't add to any stack. */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container")
	virtual bool CanAddItem(const FRPGItemInstance& ItemInstance, int32 Slot = -1) = 0;

	/* Returns the first available empty slot or stack to add to */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container", meta = (DisplayName = "GetFirstAvailableSlot"))
	virtual int32 GetFirstAvailableSlotForItem(const FRPGItemInstance& ItemInstance) const = 0;

	/* Returns the first available empty slot */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container")
	virtual int32 GetFirstAvailableSlot() const = 0;

	/* Is the specified slot occupied or empty? */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container")
	virtual bool IsSlotOccupied(int32 Slot) const = 0;
#pragma endregion Queries

#pragma region Functions
	/* Add an item */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container")
	virtual bool AddItem(const FRPGItemInstance& ItemInstance, int32 Slot = -1) = 0;

	/* Remove an item */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container")
	virtual bool RemoveItem(int32 Slot) = 0;

	/* Drops an item */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container")
	virtual bool DropItem(const FRPGItemInstance& ItemInstance) = 0;

	/* Swap item within the same container */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container")
	virtual bool SwapItem(int32 SourceSlot, int32 DestinationSlot) = 0;

	/* Splits and item stack by the specified count. The balance is returned. If the count is -1, the stack is split in half. */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container")
	virtual int32 SplitStack(FRPGItemInstance& ItemInstance, int32 SplitCount = -1) = 0;

	/* Transfer an item from this container to another */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container")
	virtual bool TransferItem(int32 SourceSlot, TScriptInterface<IRPGContainerInstanceInterface>& DestinationContainer, int32 DestinationSlot) = 0;
#pragma endregion Functions
};
