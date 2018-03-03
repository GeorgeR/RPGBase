#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Container.h"

#include "ContainerInstanceComponent.generated.h"

/* An actual instance of a container */
UCLASS(BlueprintType)
class RPGBASE_API UContainerInstanceComponent
	: public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UContainer* Container;

	UContainerInstanceComponent();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Base|Container")
	const int32 GetCapacity() const { return Container->GetCapacity(); }

	/* Adds an item to the container, returns true if it was added. InSlot == -1 means add it to the first available slot. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Container")
	bool AddItem(const FItemInstance& InItem, int32 InSlot = -1);
	virtual bool AddItem_Implementation(const FItemInstance& InItem, int32 InSlot = -1);

	/* Respond to this for UI stuff */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Container")
	void OnItemAdded(const FItemInstance& InItem);
	virtual void OnItemAdded_Implementation(const FItemInstance& InItem) { }

	/* Removes an the item at the specified slot, returns the item that was removed. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Container")
	FItemInstance RemoveItem(int32 InSlot);
	virtual FItemInstance RemoveItem_Implementation(int32 InSlot);

	/* Respond to this for UI stuff */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Container")
	void OnItemRemoved(FItemInstance& InItem);
	virtual void OnItemRemoved_Implementation(FItemInstance& InItem) { }

	/* Swaps items between the specified slots. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Container")
	void SwapItems(int32 InSlotLeft, int32 InSlotRight);
	virtual void SwapItems_Implementation(int32 InSlotLeft, int32 InSlotRight);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(BlueprintReadOnly, Replicated)
	FItemInstanceArray Items;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_AddItem(const FItemInstance& InItem, int32 InSlot = -1);
	virtual bool Server_AddItem_Validate(const FItemInstance& InItem, int32 InSlot = -1);
	virtual void Server_AddItem_Implementation(const FItemInstance& InItem, int32 InSlot = -1);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_RemoveItem(int32 InSlot);
	virtual bool Server_RemoveItem_Validate(int32 InSlot);
	virtual void Server_RemoveItem_Implementation(int32 InSlot);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SwapItems(int32 InSlotLeft, int32 InSlotRight);
	virtual bool Server_SwapItems_Validate(int32 InSlotLeft, int32 InSlotRight);
	virtual void Server_SwapItems_Implementation(int32 InSlotLeft, int32 InSlotRight);

	/* Returns first available slot index, -1 if none available. */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container")
	int32 GetFirstAvailableSlot();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Base|Container")
	FORCEINLINE bool IsSlotInRange(int32 InSlot) { return Container->IsSlotInRange(InSlot); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Base|Container")
	bool IsSlotOccupied(int32 InSlot);
};