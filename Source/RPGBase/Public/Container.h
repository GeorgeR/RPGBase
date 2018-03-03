#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item.h"

#include "Container.generated.h"

/* Create a child of this to create a container type, like a chest or inventory. */
UCLASS(BlueprintType, Blueprintable)
class RPGBASE_API UContainer
	: public UObject
{
	GENERATED_BODY()

public:
	/* Name of the container, ie. Inventory. Should be unique. */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName Name;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 ColumnCount = 4;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 RowCount = 4;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Base|Container")
	const int32 GetCapacity() const { return ColumnCount * RowCount; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Base|Container")
	FORCEINLINE bool IsSlotInRange(int32 InSlot) { return InSlot >= 0 && InSlot < GetCapacity(); }
};