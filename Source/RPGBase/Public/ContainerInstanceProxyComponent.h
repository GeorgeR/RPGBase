#pragma once

#include "CoreMinimal.h"
#include "ItemInstance.h"
#include "Components/ActorComponent.h"
#include "ProxySupport.h"
#include "ContainerInstanceComponent.h"

#include "ContainerInstanceProxyComponent.generated.h"

/* Wrapper to call RPC's for a Container via a PlayerController */
UCLASS(BlueprintType)
class RPGBASE_API UContainerInstanceProxyComponent
	: public UActorComponent,
	public TProxy<UContainerInstanceComponent>
{
	GENERATED_BODY()

private:
	friend class UContainerInstanceComponent;

	UPROPERTY()
	UContainerInstanceComponent* Context;

	void SetContextAs(UContainerInstanceComponent* InContext) override;
	UContainerInstanceComponent* GetContextAs() const override;

	UPROPERTY()
	TArray<float> ItemTimestamps;
	
	UFUNCTION(Client, Reliable)
	void Client_Page(float InTimeStamp, const TMap<int32, FItemInstance>& InPage);
	virtual void Client_Page_Implementation(float InTimeStamp, const TMap<int32, FItemInstance>& InPage);

	/* Client wants to add an item */
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_AddItem(const FItemInstance& InItem, int32 InSlot = -1);
	virtual bool Server_AddItem_Validate(const FItemInstance& InItem, int32 InSlot = -1);
	virtual void Server_AddItem_Implementation(const FItemInstance& InItem, int32 InSlot = -1);

	/* Server says adding item is ok! */
	UFUNCTION(Client, Reliable)
	void Client_AddItem(float InTimeStamp, const FItemInstance& InItem, int32 InSlot = -1);
	virtual void Client_AddItem_Implementation(float InTimeStamp, const FItemInstance& InItem, int32 InSlot = -1);

	/* Client wants to remove an item */
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_RemoveItem(int32 InSlot);
	virtual bool Server_RemoveItem_Validate(int32 InSlot);
	virtual void Server_RemoveItem_Implementation( int32 InSlot);

	UFUNCTION(Client, Reliable)
	void Client_RemoveItem(float InTimeStamp, int32 InSlot);
	virtual void Client_RemoveItem_Implementation(float InTimeStamp, int32 InSlot);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SwapItems(int32 InSourceSlot, int32 InDestinationSlot);
	virtual bool Server_SwapItems_Validate(int32 InSourceSlot, int32 InDestinationSlot);
	virtual void Server_SwapItems_Implementation(int32 InSourceSlot, int32 InDestinationSlot);

	UFUNCTION(Client, Reliable)
	void Client_SwapItems(float InTimeStamp, int32 InSourceSlot, int32 InDestinationSlot);
	virtual void Client_SwapItems_Implementation(float InTimeStamp, int32 InSourceSlot, int32 InDestinationSlot);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_TransferItem(int32 InSourceSlot, UContainerInstanceComponent* InDestinationContainer, int32 InDestinationSlot);
	virtual bool Server_TransferItem_Validate(int32 InSourceSlot, UContainerInstanceComponent* InDestinationContainer, int32 InDestinationSlot);
	virtual void Server_TransferItem_Implementation(int32 InSourceSlot, UContainerInstanceComponent* InDestinationContainer, int32 InDestinationSlot);

	UFUNCTION(Client, Reliable)
	void Client_TransferItem(float InTimeStamp, int32 InSourceSlot, UContainerInstanceComponent* InDestinationContainer, int32 InDestinationSlot);
	virtual void Client_TransferItem_Implementation(float InTimeStamp, int32 InSourceSlot, UContainerInstanceComponent* InDestinationContainer, int32 InDestinationSlot);

	inline bool IsNewer(float InTimeStamp, int32 InSlot);
	void SetItemIfNewer(float InTimeStamp, const FItemInstance& InItem, int32 InSlot);
};