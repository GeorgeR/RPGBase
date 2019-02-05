#include "ContainerInstanceProxyComponent.h"
#include "ContainerInstanceComponent.h"

void UContainerInstanceProxyComponent::SetContextAs(UContainerInstanceComponent* InContext)
{
	ItemTimestamps.Empty();

	Context = InContext;
	ItemTimestamps.Init(-1, Context->GetCapacity());
}

UContainerInstanceComponent* UContainerInstanceProxyComponent::GetContextAs() const
{
	return Context;
}

void UContainerInstanceProxyComponent::Client_Page_Implementation(float InTimeStamp, const TMap<int32, FRPGItemInstance>& InPage)
{
	check(Context);

	for(auto& KVP : InPage)
		SetItemIfNewer(InTimeStamp, KVP.Value, KVP.Key);
}

// All these do is essentially ensure the wrapped calls are run on the server
bool UContainerInstanceProxyComponent::Server_AddItem_Validate(const FRPGItemInstance& InItem, int32 InSlot /*= -1*/) { return true; }
void UContainerInstanceProxyComponent::Server_AddItem_Implementation(const FRPGItemInstance& InItem, int32 InSlot /*= -1*/)
{
	check(Context);
	Context->AddItem(InItem, InSlot);
}

void UContainerInstanceProxyComponent::Client_AddItem_Implementation(float InTimeStamp, const FRPGItemInstance& InItem, int32 InSlot)
{
	check(Context);

	if (IsNewer(InTimeStamp, InSlot))
		Context->AddItem(InItem, InSlot);
}

bool UContainerInstanceProxyComponent::Server_RemoveItem_Validate(int32 InSlot) { return true; }
void UContainerInstanceProxyComponent::Server_RemoveItem_Implementation(int32 InSlot)
{
	check(Context);
	Context->RemoveItem(InSlot);
}

void UContainerInstanceProxyComponent::Client_RemoveItem_Implementation(float InTimeStamp, int32 InSlot)
{
	check(Context);

	if (IsNewer(InTimeStamp, InSlot))
		Context->RemoveItem(InSlot);
}

bool UContainerInstanceProxyComponent::Server_SwapItems_Validate(int32 InSourceSlot, int32 InDestinationSlot) { return true; }
void UContainerInstanceProxyComponent::Server_SwapItems_Implementation(int32 InSourceSlot, int32 InDestinationSlot)
{
	check(Context);
	Context->SwapItems(InSourceSlot, InDestinationSlot);
}

void UContainerInstanceProxyComponent::Client_SwapItems_Implementation(float InTimeStamp, int32 InSourceSlot, int32 InDestinationSlot)
{
	check(Context);

	if (IsNewer(InTimeStamp, InSourceSlot) && IsNewer(InTimeStamp, InDestinationSlot))
		Context->SwapItems(InSourceSlot, InDestinationSlot);
}

bool UContainerInstanceProxyComponent::Server_TransferItem_Validate(int32 InSourceSlot, UContainerInstanceComponent* InDestinationContainer, int32 InDestinationSlot) { return true; }
void UContainerInstanceProxyComponent::Server_TransferItem_Implementation(int32 InSourceSlot, UContainerInstanceComponent* InDestinationContainer, int32 InDestinationSlot)
{
	check(Context);
	Context->TransferItem(InSourceSlot, InDestinationContainer, InDestinationSlot);
}

void UContainerInstanceProxyComponent::Client_TransferItem_Implementation(float InTimeStamp, int32 InSourceSlot, UContainerInstanceComponent* InDestinationContainer, int32 InDestinationSlot)
{
	check(Context);

	if (IsNewer(InTimeStamp, InSourceSlot))
		Context->TransferItem(InSourceSlot, InDestinationContainer, InDestinationSlot);
}

bool UContainerInstanceProxyComponent::IsNewer(float InTimeStamp, int32 InSlot)
{
	const auto bIsNewer = ItemTimestamps[InSlot] < InTimeStamp;
	if (bIsNewer)
		ItemTimestamps[InSlot] = InTimeStamp;

	return bIsNewer;
}

void UContainerInstanceProxyComponent::SetItemIfNewer(float InTimeStamp, const FRPGItemInstance& InItem, int32 InSlot)
{
	if (IsNewer(InTimeStamp, InSlot))
	{
		ItemTimestamps[InSlot] = InTimeStamp;
		Context->Items[InSlot] = InItem;
	}
}
