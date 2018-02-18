#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item.h"

#include "ContainerComponent.generated.h"

UCLASS(BlueprintType)
class RPGBASE_API UContainerComponent
	: public UActorComponent
{
	GENERATED_BODY()

public:
#pragma region Immutable Properties
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 ColumnCount = 4;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 RowCount = 4;
#pragma endregion Immutable Properties

	UContainerComponent();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Base|Container")
	const int32 GetCapacity() const { return ColumnCount * RowCount; }

	/* Adds an item to the container, returns true if it was added. InSlot == -1 means add it to the first available slot. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Container")
	bool AddItem(UItem* InItem, int32 InSlot = -1);

	/* Removes an the item at the specified slot, returns the item that was removed. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Container")
	UItem* RemoveItem(int32 InSlot);

	/* Swaps items between the specified slots. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Container")
	void SwapItems(int32 InSlotLeft, int32 InSlotRight);
	
protected:
	UPROPERTY()
	TArray<UItem*> Items;

	/* Returns first available slot index, -1 if none available. */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container")
	int32 GetFirstAvailableSlot();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Base|Container")
	FORCEINLINE bool IsSlotInRange(int32 InSlot) { return InSlot >= 0 && InSlot < GetCapacity(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Base|Container")
	FORCEINLINE bool IsSlotOccupied(int32 InSlot) { return IsSlotInRange(InSlot) && Items[InSlot] != nullptr && Items[InSlot]->GetClass() != UNullItem::StaticClass(); }
};