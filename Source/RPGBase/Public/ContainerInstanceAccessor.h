#pragma once

#include "CoreMinimal.h"
#include "ItemInstance.h"

#include "ContainerInstanceAccessor.generated.h"

/* Wrapper to call RPC's for a Container via a PlayerController */
UCLASS(BlueprintType)
class RPGBASE_API UContainerInstanceAccessor
	: public UObject 
{
	GENERATED_BODY()

private:
	friend class UContainerInstanceComponent;

	UPROPERTY()
	TMap<int, float> LRUCache;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_AddItem(UContainerInstanceComponent* InContext, const FItemInstance& InItem, int32 InSlot = -1);
	virtual bool Server_AddItem_Validate(UContainerInstanceComponent* InContext, const FItemInstance& InItem, int32 InSlot = -1);
	virtual void Server_AddItem_Implementation(UContainerInstanceComponent* InContext, const FItemInstance& InItem, int32 InSlot = -1);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_RemoveItem(UContainerInstanceComponent* InContext, int32 InSlot);
	virtual bool Server_RemoveItem_Validate(UContainerInstanceComponent* InContext, int32 InSlot);
	virtual void Server_RemoveItem_Implementation(UContainerInstanceComponent* InContext, int32 InSlot);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SwapItems(UContainerInstanceComponent* InContext, int32 InSourceSlot, int32 InDestinationSlot);
	virtual bool Server_SwapItems_Validate(UContainerInstanceComponent* InContext, int32 InSourceSlot, int32 InDestinationSlot);
	virtual void Server_SwapItems_Implementation(UContainerInstanceComponent* InContext, int32 InSourceSlot, int32 InDestinationSlot);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_TransferItem(UContainerInstanceComponent* InContext, int32 InSourceSlot, UContainerInstanceComponent* InDestinationContainer, int32 InDestinationSlot);
	virtual bool Server_TransferItem_Validate(UContainerInstanceComponent* InContext, int32 InSourceSlot, UContainerInstanceComponent* InDestinationContainer, int32 InDestinationSlot);
	virtual void Server_TransferItem_Implementation(UContainerInstanceComponent* InContext, int32 InSourceSlot, UContainerInstanceComponent* InDestinationContainer, int32 InDestinationSlot);
};