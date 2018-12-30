#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Container.h"
#include "Item.h"
#include "ItemInstance.h"

#include "ContainerInstanceComponent.generated.h"

/* An actual instance of a container */
UCLASS(BlueprintType)
class RPGBASE_API UContainerInstanceComponent
	: public UActorComponent
{
	GENERATED_BODY()

public:
	/* Unique Id of the instance */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Replicated)
	FName Id;

	/* Set this via SetContainerClass, don't set this directly! */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FSoftClassPath ContainerClass;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Replicated)
	FName OwnerId;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAdded, const FItemInstance&, InItem, int32, InSlot);
	UPROPERTY(BlueprintAssignable)
	FOnItemAdded OnItemAdded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemRemoved, const FItemInstance&, InItem, int32, InSlot);
	UPROPERTY(BlueprintAssignable)
	FOnItemRemoved OnItemRemoved;

	UContainerInstanceComponent();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Base|Container")
	int32 GetCapacity() { return GetContainer()->GetCapacity(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Base|Container")
	void SetContainerClass(FSoftClassPath& InContainerClass);

	/* Usually return false if the container is full and you can't add to any stack. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Container")
	bool CanAddItem(const FItemInstance& InItem, int32 InSlot = -1);
	virtual bool CanAddItem_Implementation(const FItemInstance& InItem, int32 InSlot = -1);

	/* Adds an item to the container, returns true if it was added. InSlot == -1 means add it to the first available slot. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Container")
	bool AddItem(const FItemInstance& InItem, int32 InSlot = -1);
	virtual bool AddItem_Implementation(const FItemInstance& InItem, int32 InSlot = -1);

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container", meta = (DisplayName = "AddItem"))
	bool AddItem_MP(APlayerController* InPlayer, const FItemInstance& InItem, int32 InSlot = -1);

	/* Removes an the item at the specified slot, returns the item that was removed. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Container")
	void RemoveItem(int32 InSlot);
	virtual void RemoveItem_Implementation(int32 InSlot);

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container", meta = (DisplayName = "RemoveItem"))
	void RemoveItem_MP(APlayerController* InPlayer, int32 InSlot);

	/* Swaps items between the specified slots. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Container")
	void SwapItems(int32 InSourceSlot, int32 InDestinationSlot);
	virtual void SwapItems_Implementation(int32 InSourceSlot, int32 InDestinationSlot);

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container", meta = (DisplayName = "SwapItem"))
	void SwapItems_MP(APlayerController* InPlayer, int32 InSourceSlot, int32 InDestinationSlot);

	/* Transfer an item between containers. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Container")
	bool TransferItem(int32 InSourceSlot, UContainerInstanceComponent* InDestinationContainer, int32 InDestinationSlot);
	virtual bool TransferItem_Implementation(int32 InSourceSlot, UContainerInstanceComponent* InDestinationContainer, int32 InDestinationSlot);

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container", meta = (DisplayName = "TransferItem"))
	bool TransferItem_MP(APlayerController* InPlayer, int32 InSourceSlot, UContainerInstanceComponent* InDestinationContainer, int32 InDestinationSlot);

	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container")
	static class UContainerInstanceProxyComponent* CreateProxy(UContainerInstanceComponent* InContainerInstance);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<FItemInstance> Items;

	/* Returns first available slot index, -1 if none available. */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container")
	int32 GetFirstAvailableSlot();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Base|Container")
	FORCEINLINE bool IsSlotInRange(int32 InSlot) { return GetContainer()->IsSlotInRange(InSlot); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Base|Container")
	bool IsSlotOccupied(int32 InSlot);
	
private:
	friend class UContainerInstanceProxyComponent;

	UPROPERTY(Transient)
	class UContainer* CachedContainer;

	const class UContainer* GetContainer();
};
