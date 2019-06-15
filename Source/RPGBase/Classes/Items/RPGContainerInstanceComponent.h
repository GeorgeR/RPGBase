#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Items/RPGContainer.h"
#include "Items/RPGItem.h"
#include "Items/RPGItemInstance.h"

#include "RPGContainerInstanceComponent.generated.h"

class IRPGUserInterface;

/* An actual instance of a container */
UCLASS(BlueprintType)
class RPGBASE_API URPGContainerInstanceComponent
	: public UActorComponent
{
	GENERATED_BODY()

public:
	/* Unique Id of the instance */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Replicated)
	FString Id;

	/* Set this via SetContainerClass, don't set this directly! */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, BlueprintSetter = "SetContainerClass")
	FSoftClassPath ContainerClass;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Replicated)
	TScriptInterface<IRPGUserInterface> Owner;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAdded, const FRPGItemInstance&, Item, int32, Slot);

	UPROPERTY(BlueprintAssignable)
	FOnItemAdded OnItemAdded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemRemoved, const FRPGItemInstance&, Item, int32, Slot);

	UPROPERTY(BlueprintAssignable)
	FOnItemRemoved OnItemRemoved;

	URPGContainerInstanceComponent();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Base|Container")
	int32 GetCapacity() { return GetContainer()->GetCapacity(); }

	UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "RPG Base|Container")
	void SetContainerClass(UPARAM(DisplayName = "ContainerClass") FSoftClassPath& InContainerClass);

#pragma region Add
	/* Usually return false if the container is full and you can't add to any stack. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Container")
	bool CanAddItem(const TScriptInterface<IRPGUserInterface>& Instigator, const FRPGItemInstance& Item, int32 Slot = -1);
	virtual bool CanAddItem_Implementation(const TScriptInterface<IRPGUserInterface>& Instigator, const FRPGItemInstance& Item, int32 Slot = -1);

	/* Adds an item to the container, returns true if it was added. InSlot == -1 means add it to the first available slot. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Container")
	bool AddItem(const TScriptInterface<IRPGUserInterface>& Instigator, const FRPGItemInstance& Item, int32 Slot = -1);
	virtual bool AddItem_Implementation(const TScriptInterface<IRPGUserInterface>& Instigator, const FRPGItemInstance& Item, int32 Slot = -1);
#pragma endregion Add

#pragma region Remove
	/* Removes an the item at the specified slot, returns the item that was removed. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Container")
	void RemoveItem(const TScriptInterface<IRPGUserInterface>& Instigator, int32 Slot);
	virtual void RemoveItem_Implementation(const TScriptInterface<IRPGUserInterface>& Instigator, int32 Slot);
#pragma endregion Remove

#pragma region Swap
	/* Swaps items between the specified slots. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Container")
	void SwapItems(const TScriptInterface<IRPGUserInterface>& Instigator, int32 SourceSlot, int32 DestinationSlot);
	virtual void SwapItems_Implementation(const TScriptInterface<IRPGUserInterface>& Instigator, int32 SourceSlot, int32 DestinationSlot);
#pragma endregion Swap

#pragma region Transfer
	/* Transfer an item between containers. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Container")
	bool TransferItem(const TScriptInterface<IRPGUserInterface>& Instigator, int32 SourceSlot, URPGContainerInstanceComponent* InDestinationContainer, int32 DestinationSlot);
	virtual bool TransferItem_Implementation(const TScriptInterface<IRPGUserInterface>& Instigator, int32 SourceSlot, URPGContainerInstanceComponent* DestinationContainer, int32 DestinationSlot);
#pragma endregion Transfer

	//UFUNCTION(BlueprintCallable, Category = "RPG Base|Container")
	//static class UContainerInstanceProxyComponent* CreateProxy(URPGContainerInstanceComponent* ContainerInstance);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<FRPGItemInstance> Items;

	/* Returns first available slot index, -1 if none available. */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Container")
	int32 GetFirstAvailableSlot();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Base|Container")
	FORCEINLINE bool IsSlotInRange(int32 Slot) { return GetContainer()->IsSlotInRange(Slot); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Base|Container")
	bool IsSlotOccupied(int32 Slot);
	
private:
	friend class UContainerInstanceProxyComponent;

	UPROPERTY(Transient)
	class URPGContainer* CachedContainer;

	const class URPGContainer* GetContainer();
};
